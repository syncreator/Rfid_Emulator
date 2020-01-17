#include <avr/pgmspace.h>
#include <MsTimer2.h>
#include <Button.h>
#include <EEPROM.h>
#include <OLED_I2C.h>
#include "watch.h"

#define LED_1_PIN    9   // светодиод подключен к выводу 9
#define BUTTON_1_PIN 0  // кнопка подключена к выводу 0
#define BUTTON_2_PIN 1  // кнопка подключена к выводу 1

#define COUNT   16  // кол-во файлов меню 16
#define FCOUNT  11  // кол-во файлов конфигменю 11
//#define FILEREW  4  // кол-во параметров в файле 4
#define NUM      6  // кол-во ячеек памяти для записи ключей
#define PX       4 // максимальное кол-во строк помещающихся на экране(для меню текстовых списков)
//Type Configs
#define T_1       0 // Time_type1
#define T_2       1 // Time_type2
#define BOOL      2 // Boolean (on/off)
#define INT       3 // Integer type

//File types definitions
#define T_FOLDER   0 // Folder file#define T_DFOLDER 
#define T_DFOLDER  1 // Dynamic Folder
#define T_APP      2 // Application
#define T_CONFIG   3 // Config file

Button button1(BUTTON_1_PIN, 0);  // создание объекта - кнопка1
Button button2(BUTTON_2_PIN, 1);  // создание объекта - кнопка2
OLED  myOLED(SDA, SCL, 8);
/*namespace ns {
OLED  myOLED(SDA, SCL, 8);
Button button1(BUTTON_1_PIN, 0);  // создание объекта - кнопка1
//Button button2(BUTTON_2_PIN, 1);  // создание объекта - кнопка2
}
using namespace ns;*/

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t check_14x10[];
extern uint8_t check1_14x10[];
extern uint8_t arrow_13x10[];
extern uint8_t arrow1_13x10[];
extern uint8_t key1[];
extern uint8_t menu_alarm[];
extern uint8_t menu_exit[];
extern uint8_t menu_settings[];
extern uint8_t menu_sleep[];
extern uint8_t menu_tunemaker[];
extern uint8_t selectbar_top[];
extern uint8_t selectbar_bottom[];
extern uint8_t torch[];
extern uint8_t pacman32[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];
extern uint8_t alarm15x14[];
extern uint8_t minialarm[];

volatile int _Menu(0),_Pos(1),_tes(1),Config_flag(0);//,Launch_APP(0); //_Pos нумеруется с 1!!!
//char ti[] = "<>"; //вспомоательный массив для добавления ковычек в заголовок

uint8_t* bm;
int pacy;
char b[16];
unsigned long prevTime;  // предыдущее значение времени
//unsigned long curTime;  // текущее значение времени

//массив указателей на иконки меню.
uint8_t* const fp[]PROGMEM = {pacman32, key1, torch, menu_alarm, menu_tunemaker, menu_settings, menu_sleep, menu_exit};
char const KName[]PROGMEM = {"Home Work_1 Work_2 VIP_key Office_key Exit"};
//char* const KeyName[]PROGMEM = {"Home", "Work_1", "Work_2", "VIP_key", "Office_key", "Exit"};
char const MName[]PROGMEM = {"Star_Wars Melody#1 Melody#2 Melody#3 Melody#4 Exit"};
char const CName[]PROGMEM = {"Time_Emulate Time_Read Exit Volume Exit Time Alarm_Time Alarm_Clock Exit Red Blue Green Brightness Program Exit"};
char const MENU_N[]PROGMEM = {"Main_Menu Key_Read Key_Emulate Torch Watch Music Config_menu Sleep Exit Key# Melody# RFID_Config Music_Config Watch_Config Torch_Config Exit"};
//Структура меню
struct MENU{
  uint8_t type;
  uint8_t parent;
  uint8_t id_dot;
  uint8_t f_num;
 // char f_name[];
};
//Структура конфигов
struct CONFIG{//
  uint8_t type;
  int c_max;
  int def;
};

char* plr(char*,int);
void fix(int, int);
void Pacman();
void Menu();
void List_menu(int,int);
void Config_app();
void destr(byte, int);
int constr(byte);
void wait(int);
void scroll();
void Watch(OLED &myOLED, Button &button1, Button &button2, uint8_t* bm, unsigned long St_time=0, unsigned long X_point=0, unsigned int alarm_time=0, int alarm_flag=0);

void Enter_render();
void Arow_render();

//char *curr = b;
//menu struct
static const MENU MStruct [COUNT]PROGMEM=
{
  T_FOLDER, 0, 1, 8,    //0 "Root"(ROOT FILE)
  T_APP, 0, 1, 0,       //1 "Key_Capture" Catch app
  T_DFOLDER, 0, 9, NUM, //2 "Key_Emulate" Key folder
  T_APP, 0, 2, 0,       //3 "Torch" flashlight app
  T_APP, 0, 3, 0,       //4 "Watch" Clock app
  T_DFOLDER, 0, 10, NUM,//5 "Music" Melody app
  T_FOLDER, 0, 11, 5,   //6 "Config" 4-Configs
  T_APP, 0, 4, 0,       //7 "Sleep" Sleep app
  T_APP, 0, 5, 0,       //8 "Exit" Exit to Clock app
  T_APP, 2, 6, 0,       //9 "Key_N" Key app folder
  T_APP, 5, 7, 0,       //10 "Melody_N" app folder musik
  T_CONFIG, 6, 1, 3,    //11 RFID_Config
  T_CONFIG, 6, 2, 2,    //12 Music_Config
  T_CONFIG, 6, 3, 4,    //13 Watch_Config
  T_CONFIG, 6, 4, 6,    //14 Torch_Config
  T_APP, 6, 8, 0,       //15 Exit to Maine Menu
};


//массив лимитов и значений по умолчанию конфигов меню.
static const CONFIG ConfigLim[FCOUNT]PROGMEM = {
  T_1, 180, 4,  //0 Time_Emulate
  T_1, 180, 4,  //1 Time_Read
  INT, 5, 2,    //2 Volume
  T_2, 1440, 0, //3 Time_set
  T_2, 1440, 0, //4 Alarm_Time
  BOOL,1, 0,    //5 Alarm_Clock
  BOOL,1, 1,    //6 RED
  BOOL,1, 1,    //7 BLUE
  BOOL,1, 1,    //8 GREEN
  INT, 5, 3,    //9 Brightnees
  INT, 3, 1,    //10 Volume
};

void setup()
{
  pinMode(LED_1_PIN, OUTPUT);// определяем вывод светодиода как выход
  // pinMode(BUTTON_1_PIN, INPUT_PULLUP);// определяем вывод кнопки 1 как вход
  // pinMode(BUTTON_2_PIN, INPUT_PULLUP); определяем вывод кнопки 2 как вход
  MsTimer2::set(2, timerInterupt); // задаем период прерывания по таймеру 2 мс
  MsTimer2::start();              // разрешаем прерывание по таймеру
  myOLED.begin();
  myOLED.setFont(SmallFont);
  randomSeed(analogRead(7));

  myOLED.clrScr();
  myOLED.print("YORIK INDASTRY", CENTER, 0);
  myOLED.print("present", CENTER, 12);
  myOLED.print("RFID Key", CENTER, 28);
  myOLED.drawRoundRect(23, 25, 103, 37);
  myOLED.print("(C)2017 by", CENTER, 47);
  myOLED.print("Yuriy Savichev", CENTER, 57);
  myOLED.update();

  delay(6000);

  myOLED.clrScr();

  //Main menu screen
  myOLED.clrScr();
  myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
  myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
  myOLED.drawRoundRect(1, 0, 17, 13);
  myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Main_Menu>", CENTER, 0);
  myOLED.drawBitmap(46, 11, selectbar_top, 36, 8);
  myOLED.drawBitmap(46, 46, selectbar_bottom, 36, 8);
  myOLED.printNumI(_Pos, 3, 57);
  //curr = (char*)pgm_read_byte(&KName[0]);
  //myOLED.print(((char*)curr->f_name)/*((char*)pgm_read_word(&(MStruct[_Pos].f_name)))*/, 15, 57);
  myOLED.print((plr(MENU_N,1)),15, 57);
  fix(3,1);
  myOLED.update();
  delay(10);
  //// EEPROM for ConfigLimits
  for(byte i=0;i<=10;i++)
  if ((EEPROM[i*2]==255 && EEPROM[i*2+1]==255) || constr(i)>((uint16_t)pgm_read_word(&(ConfigLim[i].c_max))))
  destr(i,(uint8_t)pgm_read_word(&(ConfigLim[i].def)));
  /*Serial.begin(9600); // инициализация послед. порта
  //Отработка монитора посл. порта:
  for (int addr=0; addr<50; addr++) { // для всех ячеек памяти (для Arduino UNO 1024)
    byte val =EEPROM.read(addr); // считываем 1 байт по адресу ячейки
    Serial.print(addr);
    Serial.print("\t");// выводим адрес в послед. порт 
    if (addr%2){Serial.print(val,DEC);Serial.print("\t");Serial.print(EEPROM[addr-1]*255+EEPROM[addr],DEC);Serial.print("\t");Serial.println((uint16_t)pgm_read_word(&(ConfigLim[(addr-1)/2].c_max)),DEC);} // выводим значение в послед. порт
    else Serial.println(val,DEC);
  }
  delay(6000); // задержка 1 мин
  //Конец отработки монитора посл. порта:)*/
  //Начало отчета времени для часов
  prevTime=Time(constr(3),constr(9)*65535+constr(10));//millis();  // предыдущее значение времени

}

void loop()
{
  if ( button1.flagClick == true ) {
    // был клик кнопки
    button1.flagClick = false;        // сброс признака
    Arow_render();
    //Menu();
  }
  
  if ( button2.flagClick == true ) {
    // был клик кнопки
    button2.flagClick = false;        // сброс признака
    Enter_render();
    //Pacman();
  }
  ////////////////// бегущая строка
  //scroll();
  ///////////////// Часы
  if(prevTime!=Time(constr(3),constr(9)*65535+constr(10))/*+1000<=millis()*/&& _Menu==0){prevTime=Time(constr(3),constr(9)*65535+constr(10));//millis();
                             myOLED.printNumI(prevTime/60/60, 78, 57,2,'0'); //часы
                             if((prevTime%60)%2)myOLED.print(":", 91, 57);
                             else myOLED.print(" ", 91, 57);
                             myOLED.printNumI((prevTime/60)%60, 96, 57,2,'0');//минуты
                             myOLED.print(":", 109, 57);
                             myOLED.printNumI(prevTime%60, 114, 57,2,'0');//секунды
                             if(constr(5))myOLED.drawBitmap(69, 57, minialarm, 8, 8);
                             else {myOLED.print(" ", 69, 57);
                             myOLED.print(" ", 71, 57);
                             }
                             myOLED.update();
  }
}
// обработчик прерывания
void  timerInterupt() {
  button1.scanState();// вызов метода ожидания стабильного состояния для кнопки1
  button2.scanState();// вызов метода ожидания стабильного состояния для кнопки2
}
//////////////////// аналог delay() без остановки программы
void wait(int t)
{unsigned long x=millis();
 while((millis()-x)<t){if ( (button1.flagClick || button2.flagClick) == true )
        // был клик кнопки 1
        break;}
}
//////////////////////
void scroll()
{ volatile static int _i=128;

  if(_Menu)while(_i>=-(36*6))
  {
    if ((button1.flagClick || button2.flagClick) == true )
        // был клик кнопки 1
        //_i=i;//сохраним i на котором вышли из цикла
        break;
       // if(i==-(36*6))_it=128;
    myOLED.print("Here could be your Advertising!!!!!!", _i, 56);
    myOLED.update();
    wait(50);
     _i--;
     if(_i<-(36*6))_i=128;
  }
  else _i=128;
  }
//////////////////////
void Pacman()
{ myOLED.clrScr();
  for (int pc = 0; pc < 3; pc++)
  {
    if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
    pacy = random(20, 44);
    //int j=0;
    for (int i = -20,j=0; i < 132; i++,j++)
    {
      if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
      myOLED.clrScr();
      for (int p = 6; p > ((i + 20) / 20); p--)
      {
        if ( button1.flagClick == true )
          // был клик кнопки 1
          break;
        if (random(0, 100) % 2)myOLED.print("0", p * 20 - 8, pacy + 7);
        else myOLED.print("1", p * 20 - 8, pacy + 7); //drawBitmap(p*20-8, pacy+7, "1", 5, 5);
      }
      if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
      switch (((i + 20) / 3) % 4)
      {
        case 0: bm = pacman1;
          break;
        case 1: bm = pacman2;
          break;
        case 2: bm = pacman3;
          break;
        case 3: bm = pacman2;
          break;
      }
      myOLED.drawBitmap(i, pacy, bm, 20, 20);
      if (j<=3)myOLED.print("KEY READ      ", CENTER, 0);
      if ((j>3)&&(j<=6))myOLED.print("KEY READ .    ", CENTER, 0);
      if ((j>6)&&(j<=9))myOLED.print("KEY READ . .  ", CENTER, 0);
      if ((j>9)&&(j<=12))myOLED.print("KEY READ . . .", CENTER, 0);
      if (j==12)j=0;
      myOLED.update();
      delay(10);
    }
  }
  //if(button1.flagClick==false)button2.flagClick = true;
}

//прорисовка иконок граф меню
void fix(int n, int x)//n-количество раз отрисовки иконок по циклу, х-начальная коорината иконки
{for(int i=0,j=_Pos-(n-1); i<n;i++,j++)
  {j=((j<0)?7:((j>7)?0:j));
   switch (j)
      {
        case 0: bm = pacman32;
          break;
        case 1: bm = key1;
          break;
        case 2: bm = torch;
          break;
        case 3: bm = menu_alarm;
          break;
        case 4: bm = menu_tunemaker;
          break;
        case 5: bm = menu_settings;
          break;
        case 6: bm = menu_sleep;
          break;
        case 7: bm = menu_exit;
          break;
      }
   myOLED.drawBitmap(x+i*47,17,bm,32,32);
  }
}
//Добавляет кавычки<> в строку
/*char* buf(char *a, char* b)
{ byte i(1);
  //char b[]="<>";
  while ((b[i] = a[i - 1]) != '\0')
    ++i;
  b[i] = '>';
  b[++i] = '\0';
  return b;
}*/
//Распаковщик для наименований меню
char* plr(char* s, int i)
{ int n, j,x(0), k;
  while (b[x]!= '\0')//очистка масива от предыдущей записи
    {b[x]=0;
    ++x;}
  //while(b!=curr)
  for (n = 0,j=0,k=0; (n < strlen_P(s))&&(i>=j); n++)
  {
     if(pgm_read_byte_near(s + n)==' ')j++;
     if((i==j)&& (pgm_read_byte_near(s + n)!=' '))b[k++]=pgm_read_byte_near(s + n);}
  /*for (n=0;(pgm_read_byte_near(s)!= '\0')&&(i>n);s++)
    if(pgm_read_byte_near(s)==' ')n++;
  for (j=0;(pgm_read_byte_near(s)!= '\0')&&(pgm_read_byte_near(s)!=' ');s++,j++)
    {b[j]=pgm_read_byte_near(s);
    b[++j]='\0';}*/
    return b;
}
//***********************//
void Menu()
{ //Main menu screen
  //first frame:
  myOLED.clrScr();
  myOLED.drawBitmap(3, 2, arrow1_13x10, 13, 10);
  myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
  myOLED.drawRoundRect(1, 0, 17, 13);
  myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Main_Menu>", CENTER, 0);
  myOLED.drawBitmap(46, 11, selectbar_top, 36, 8);
  myOLED.drawBitmap(46, 46, selectbar_bottom, 36, 8);
  fix(4,-22);
  myOLED.update();
  delay(100);
  
  //second frame:
  myOLED.clrScr();
  myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
  myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
  myOLED.drawRoundRect(1, 0, 17, 13);
  myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Main_Menu>", CENTER, 0);
  myOLED.drawBitmap(46, 11, selectbar_top, 36, 8);
  myOLED.drawBitmap(46, 46, selectbar_bottom, 36, 8);
  myOLED.printNumI(_Pos, 3, 57);
  myOLED.print(plr(MENU_N,_Pos)/*((char*)pgm_read_word(&(MStruct[_Pos].f_name)))*/, 15, 57);
  //myOLED.printNumI((uint8_t)pgm_read_word(&(menuStruct[FILEREW*_Menu+3])), 30, 57);
  fix(3,1);
  myOLED.update();
}
//prototip list menu screen
void List_menu(int m, int t)
{//int M=_Menu,T=_Pos;

myOLED.clrScr();
myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
myOLED.drawRoundRect(1, 0, 17, 13);
myOLED.drawRoundRect(110, 0, 127, 13);
myOLED.print(plr(MENU_N,m)/*(char*)pgm_read_word(&(MStruct[m].f_name))*/, CENTER, 0);
myOLED.drawRoundRect(1, 15, 127, 26);//Обрамление выделенного пункта меню
 int i(0),y(0), g=(uint8_t)pgm_read_word(&(MStruct[m].id_dot)), //номер дочерней папки в меню
                s =(uint8_t)pgm_read_word(&(MStruct[m].f_num)) ;  //кол-во файлов в папке
  //if (s<(T+i))y=T+i-s;else y=T+i;
  if(m==2){while (i < ((s < PX) ? s : PX))
    {if (s<(t+i))y=t+i-s;else y=t+i;
      myOLED.printNumI(y, 3, 17 + i * 10);
      myOLED.print(plr(KName,(y-1))/*(char*)pgm_read_word(&(KeyName[y-1]))*/, CENTER, 17 + i * 10 );//вызов массива названий для ключей
      ++i;
    };}
  if(m==5){while (i < ((s < PX) ? s : PX))
    {if (s<(t+i))y=t+i-s;else y=t+i;
      myOLED.printNumI(y, 3, 17 + i * 10);
      myOLED.print(plr(MName,(y-1))/*(char*)pgm_read_word(&(MusicName[y-1]))*/, CENTER, 17 + i * 10 );//вызов массива названий для мелодий
      ++i;
    };}
     else {while (i < ((s < PX) ? s : PX))
    {if (s<(t+i))y=t+i-s;else y=t+i;
      myOLED.printNumI(y, 3, 17 + i * 10);
      myOLED.print(plr(MENU_N,(g+y-1))/*(char*)pgm_read_word(&(MStruct[g+y-1].f_name))*/, CENTER, 17 + i * 10);//вызов массива названий основного списка меню
      ++i;
    };}
   /* myOLED.print("_Pos=", CENTER, 10);
  myOLED.printNumI(t, 62, 22);
  myOLED.print("_Menu=", CENTER,38 );
 // myOLED.printNumI(_Menu, 62, 50);
  //myOLED.print("file_#", 3, 57);
  myOLED.printNumI(t, 3, 57);
  //  myOLED.print(P, 45, 57);
 // myOLED.print("file_sum", 63, 57);
  myOLED.printNumI(m, 63, 57);
  //  myOLED.print(s, 113, 57);*/
  myOLED.update();
} 
/////////////

/*void Watch(uint8_t* bm, unsigned long St_time=0, unsigned long X_point=0, unsigned int alarm_time=0, int alarm_flag=0)//вывод часов на весь экран + будильник
{unsigned long  prevTime=Time(St_time,X_point);
 //Заголовок + инфа по будильнику и обрамление
 myOLED.clrScr();
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
 myOLED.drawBitmap(112, 0, bm, 15, 14);
  myOLED.drawRoundRect(1, 0, 17, 13);
 //myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Watch_app>", CENTER, 2);
 myOLED.print("ALARM",5,19 );
  //myOLED.drawBitmap(62,18, bm, 15, 14);
 if(alarm_flag) myOLED.print("_ON", 58, 19);//BOOL on/off
                    else myOLED.print("_OFF", 58, 19);
 myOLED.printNumI(alarm_time/60, 92, 19, 2,'0');//Т_2
                    myOLED.print(":",105,19);
                    myOLED.printNumI(alarm_time%60, 110, 19, 2,'0');
  myOLED.drawRoundRect(1, 14, 127, 29);
  myOLED.drawRoundRect(1, 31, 127, 63);
  myOLED.drawRoundRect(1, 31, 42, 63);
  myOLED.drawRoundRect(44, 31, 79, 63);
  myOLED.drawRoundRect(82, 31, 127, 63);
  
 //
/* for (int i=0; i<=50; i++)
  {
   // myOLED.setFont(MediumNumbers);
    //myOLED.printNumF(float(i)/3, 2, RIGHT, 0);
    //myOLED.setFont(BigNumbers);
    //myOLED.printNumI(i,64,35,4,'0');
    myOLED.drawRoundRect(36-i, 40-i, 38+i, 46+i);
    myOLED.update();
    delay(100);
  }
  //myOLED.setFont(SmallFont);
  myOLED.drawRoundRect(36, 40, 38, 46);
  myOLED.drawRoundRect(36, 50, 38, 56);
  myOLED.drawRoundRect(78, 40, 80, 46);
  myOLED.drawRoundRect(78, 50, 80, 56);
  myOLED.update();*/
  
  //////////////////////////////////

  /*while(1)
  {if ( button1.flagClick == true )
        {// был клик кнопки 1
    button1.flagClick = false;        // сброс признака
        myOLED.setFont(SmallFont);
        break;}
    if(prevTime!=Time(St_time,X_point)){prevTime=Time(St_time,X_point);
                           /* myOLED.clrScr();
                            myOLED.print("Time",5, 2);
                            myOLED.printNumI(Time(constr(3),constr(9)*65535+constr(10)), 30, 2);
                            myOLED.print("ST_time*60", 15, 11);
                            myOLED.printNumI(t, 5, 21);
                            myOLED.printNumI(t*60,40,21,5);
                            myOLED.print("X_point", 15, 32);
                            myOLED.printNumI(constr(9)*65535+constr(10), 15, 42,10);*/
                            ///////////////////////////////////////////////////////
                             /*myOLED.printNumI(prevTime/60/60, 74, 57,2,'0'); //часы
                             myOLED.print(":", 87, 57);
                             myOLED.printNumI((prevTime/60)%60, 92, 57,2,'0');//минуты
                             myOLED.print(":", 105, 57);
                             myOLED.printNumI(prevTime%60, 110, 57,2,'0');//секунды
                             myOLED.update();*/
                             //myOLED.clrScr();
                            // myOLED.setFont(/*SmallFont*/BigNumbers);
                            /* myOLED.printNumI(prevTime/60/60, 8, 37,2,'0'); //часы
                             //myOLED.drawRoundRect(41, 40, 44, 46);
                             //myOLED.drawRoundRect(41, 50, 44, 56);
                             //myOLED.print(".", 36, 56);
                             myOLED.printNumI((prevTime/60)%60, 50, 37,2,'0');//минуты
                             //myOLED.drawRoundRect(78, 40, 80, 46);
                             //myOLED.drawRoundRect(78, 50, 80, 56);
                             //myOLED.print(".", 78, 56);
                             myOLED.printNumI(prevTime%60,92 ,37,2,'0');//секунды
                             myOLED.update();
    }
  }
}*/
//////////
void destr(byte i, int x)//трансляция int x в два байтовых ЕЕПРОМА
{//byte j=i*2;
 if(x>65500)return;//проверка на мах допустивый размер числа
 EEPROM.update(i*2,x/255);
 EEPROM.update(i*2+1,x%255);
}
////////////
int constr(byte i)//Сборка int числа из двух байтов ЕЕПРОМА
{
  return (EEPROM[i*2]*255+EEPROM[i*2+1]);
}
////////////
int Config_app(int f=0)
{// 
  static int _val; //переменная буфер для хранения промежуточного значения редактируемого параметра
  uint8_t i,j,t,sum(0);//_tes(1);//переменная для определения текущей позиции в списке параметров выбранного конфига
    i=(uint8_t)pgm_read_word(&(MStruct[_Menu].id_dot));//i=11
    j=t=_Pos;
 while(j>1)
 {sum+=((uint8_t)pgm_read_word(&(MStruct[i++].f_num)));//вычисляем добавку к _tes? для правильной навигации по конфиг структуре и масиву названий параметров
 j--;}
 i=0;
 int y(0), g=(uint8_t)pgm_read_word(&(MStruct[_Menu].id_dot)), //номер дочерней папки в меню
           s =(uint8_t)pgm_read_word(&(MStruct[g+t-1].f_num));  //кол-во файлов в папке
 //обработка EEPROM данных
 if (f==1) _val=constr(sum+_tes-1-(_Pos-1));//сохраняем текущее значение конфига в _val
 if (f==2) {if(_val<((uint16_t)pgm_read_word(&(ConfigLim[sum+_tes-1-(_Pos-1)].c_max)))) _val++;
                  else _val=0;}//прибавляем 1 к _val пока не достигнет MAX значения 
 if (f==3) {destr(sum+_tes-1-(_Pos-1),_val);// сохраняем _val в EEPROM
    if (sum+_tes-1-(_Pos-1)==3){unsigned long x=millis();destr(9,(int)(x/65535));destr(10,(int)(x%65535));};//разборка millis() на 4байт EEPROM 18,19,20,21
 }// сборка в unsigned long  constr(9)*65535+constr(10)
 /// прорисовка графики
 myOLED.clrScr();
myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
myOLED.drawRoundRect(1, 0, 17, 13);
myOLED.drawRoundRect(110, 0, 127, 13);
myOLED.print(plr(MENU_N,(g+t-1)), CENTER, 0);//Заголовок
if(Config_flag==1)myOLED.drawRoundRect(1, 15, 89, 26);//Обрамление выделенного пункта меню                 
if(Config_flag==2)myOLED.drawRoundRect(90, 15, 127, 26);//Обрамление редактируемого параметра конфига
/*myOLED.printNumI(_val, 3, 57);
myOLED.printNumI((uint16_t)pgm_read_word(&(ConfigLim[sum+_tes-1-(_Pos-1)].c_max)), 20, 57);
myOLED.printNumI(sum, 38, 57);
myOLED.printNumI(Config_flag, 56, 57);*/


  while (i < ((s < PX) ? s : PX))
    {if (s<(_tes+i))y=_tes+i-s;else y=_tes+i;
      myOLED.printNumI(y, 3, 17 + i * 10);//пишем номер строки
      myOLED.print(plr(CName,(sum+y-1)),15, 17 + i * 10 );//вызов массива названий для параметров конфигов
      if(y<=(s-1))//условие попадания на строку с названием параметра(строка Exit игнорируется)
     switch ((uint8_t)pgm_read_word(&(ConfigLim[sum+y-(_Pos-1)-1].type)))//прорисовка текущих значений параметров конфигов
      {
         case 0: if(Config_flag==2 && i==0){myOLED.printNumI(_val/60, 92, 17 + i * 10, 2,'0');//Т_1
                    myOLED.print(":", 106, 17 + i * 10);
                    myOLED.printNumI(_val%60, 112, 17 + i * 10, 2,'0');}
                    else{myOLED.printNumI(constr(sum+y-1-(_Pos-1))/60, 92, 17 + i * 10, 2,'0');//Т_1
                    myOLED.print(":", 106, 17 + i * 10);
                    myOLED.printNumI(constr(sum+y-1-(_Pos-1))%60, 112, 17 + i * 10, 2,'0');}
          break;
        case 1: if(Config_flag==2 && i==0){myOLED.printNumI(_val/60, 92, 17 + i * 10, 2,'0');//Т_2
                    myOLED.print(":", 106, 17 + i * 10);
                    myOLED.printNumI(_val%60, 112, 17 + i * 10, 2,'0');}
                    else {myOLED.printNumI(constr(sum+y-1-(_Pos-1))/60, 92, 17 + i * 10, 2,'0');//Т_2
                    myOLED.print(":", 106, 17 + i * 10);
                    myOLED.printNumI(constr(sum+y-1-(_Pos-1))%60, 112, 17 + i * 10, 2,'0');}
          break;
        case 2: if(Config_flag==2 && i==0){if(_val) myOLED.print("on", 102, 17 + i * 10);//BOOL on/off
                    else myOLED.print("off", 102, 17 + i * 10);}
                 else {if(constr(sum+y-1-(_Pos-1))) myOLED.print("on", 102, 17 + i * 10);//BOOL on/off
                    else myOLED.print("off", 102, 17 + i * 10);}
          break;
        case 3: if(Config_flag==2 && i==0)myOLED.printNumI(_val, 102, 17 + i * 10);
                 else myOLED.printNumI(constr(sum+y-1-(_Pos-1)), 102, 17 + i * 10);//INT
          break;
     }
     ++i;
    };
    myOLED.update();
  }

 void Enter_render()
 { //if(_Menu==0)//находимся в графическом меню
  {myOLED.drawBitmap(112, 2, check1_14x10, 14, 10);// блымка кнопки ентер при ее нажатии:)
           myOLED.update();
           delay(50);
          }
  if((_Pos==6&&_Menu==2)||(_Pos==6&&_Menu==5)||(_Pos==5&&_Menu==6))//выход в основное меню при выборе exit в папках
  {_Pos=_Menu; _Menu=0;
    Menu();           
  }        
  else{        
  int x=((_Menu==2 ||_Menu==5)? 0 :_Pos-1)+((uint8_t)pgm_read_word(&(MStruct[_Menu].id_dot)));//x-находим номер текущего файла меню
      if (((uint8_t)pgm_read_word(&(MStruct[x].type)))==T_APP)
          switch (((uint8_t)pgm_read_word(&(MStruct[x].id_dot))))
      {
        case 1: Pacman();//Key_cap();
          break;
        case 2: Pacman();//Torch();
          break;
        case 3: Watch(myOLED, button1, button2, minialarm, constr(3),constr(9)*65535+constr(10),constr(4),constr(5));
          break;
        case 4: Pacman();//Sleep();
          break;
        case 5: Pacman();//Exit();
          break;
        case 6: Pacman();//Key_emulate();
          break;
        case 7: Pacman();//Music();
          break;
      };
      if (((uint8_t)pgm_read_word(&(MStruct[x].type)))==T_DFOLDER || ((uint8_t)pgm_read_word(&(MStruct[x].type)))==T_FOLDER)// может написать.. ==(T_DFOLDER || T_FOLDER)
      {_Menu=_Pos;
       _Pos=1;
       List_menu(_Menu,_Pos);//прорисовка списковых папок: списков ключей, мелодий, конфигов
      };
       if((Config_flag!=0)&&((_Pos==1&&_tes==3)||(_Pos==2&&_tes==2)||(_Pos==3&&_tes==4)||(_Pos==4&&_tes==6)))//выход в меню конфигов при выборе exit в папках параметров конфигов
  { Config_flag=0;
    _tes=1;
    List_menu(_Menu,_Pos);
  }
      else if(((uint8_t)pgm_read_word(&(MStruct[x].type)))==T_CONFIG)
      {if(Config_flag==2){Config_flag--;Config_app(3);}
          else{Config_flag++;Config_app(1);};
          };//?? будет выполнятся каждый раз при нажатии ентер внутри файлов T_CONFIG?
       //Config_app();
      /*switch (((uint8_t)pgm_read_word(&(MStruct[x].id_dot))))
      {
        case 1: Config_app();//Config_1();
          break;
        case 2: Config_app();///Config_2();
          break;
        case 3: Config_app();///Config_3();
          break;
        case 4: Config_app();///Config_4();
          break;
        };//функция редактирования конфигов-принимает номер выбранного конфига???????*/
      };
 }

 void Arow_render()
     {if(Config_flag!=0)//????
       {// if(Launch_APP!=0)return(0);//????
        int g=((uint8_t)pgm_read_word(&(MStruct[_Menu].id_dot)));//_Menu=6; g=11
         if(Config_flag==1)((_tes<((uint8_t)pgm_read_word(&(MStruct[g+_Pos-1].f_num))))?_tes++:_tes=1);
       myOLED.drawBitmap(3, 2, arrow1_13x10, 13, 10);
           myOLED.update();
           delay(50);
            if(Config_flag==2)Config_app(2);else Config_app(0);
       //Config_app();
       }
       else{((_Pos<((uint8_t)pgm_read_word(&(MStruct[_Menu].f_num))))?_Pos++:_Pos=1);
       if(_Menu==0)Menu();
          else
          {myOLED.drawBitmap(3, 2, arrow1_13x10, 13, 10);
           myOLED.update();
           delay(50);
           List_menu(_Menu,_Pos);
          }
        } 
     }
