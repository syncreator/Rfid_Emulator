#include <SoftwareSerial.h>
#define RDM6300_PIN    9   // Пин подключающий питание на RDM

SoftwareSerial RfidReader(0, 1);
int num[];
int count = 0;

void setup(){
pinMode(RDM6300_PIN, OUTPUT);// определяем вывод для включения RDM6300 как выход
Serial.begin(9600); 
RfidReader.begin(9600);

}
void loop() 
{
 if (RfidReader.available() > 0)
  {count++;
num = RfidReader.read();
Serial.print(num, DEC);
    if(count >= 14)
    {Serial.println(' ');
     count = 0;}
  else {
Serial.print(", ");
  }
 }
}
/////// Строчный вариант
#include <SoftwareSerial.h>
 
SoftwareSerial rdm6300(7, 8);
String s = "";
 
void setup() {
  rdm6300.begin(9600);
  Serial.begin(9600);
}
 
void loop() {
  if (rdm6300.available() > 0) {
    while (rdm6300.available() > 0) {
      char c = rdm6300.read();
      s += c;
      delay(3);
    }
 
    Serial.println(s);
    s = "";
  }
}
/////// Прилага для считывания rfid ключей
void rdm6300_read(OLED &myOLED, Button &button1, Button &button2, byte m, byte RDM6300_Pin)//m - передача параметра из конфигов(если понадобиться)
{int count(0);
 int num[14];
 digitalWrite( RDM6300_Pin,  HIGH);//Включаем rdm6300
  wait(2000);//ждем пока включиться
  //Запускаем Pacman пока rdm6300 не выдаст 14 битов?
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
     
     //Begin rdm6300 read
     /*if (RfidReader.available() > 0)
  {count++;
//num = RfidReader.read();
Serial.print(/*num*//*RfidReader.read(), DEC);
    if(count >= 14)
    {Serial.println(' ');
     count = 0;}
  else {
Serial.print(", ");
  }
 }*///END of rdm6300 read
      //delay(10);
     //wait(int t)
     {unsigned long x=millis();
 while((millis()-x)<10/*t*/){if ( (button1.flagClick || button2.flagClick) == true )break;
        // был клик кнопки 1
     if (RfidReader.available() > 0)
  {num[count++] = RfidReader.read();
Serial.print(num[count-1], DEC);
    if(count >= 14)
    {Serial.println(' ');
     count = -1;}
  else {
Serial.print(", ");
       }
  }
 }//END while()
}//END wait()
    if(count<0)break;}
  if(count<0)break;}
  if(count<0)break;//выход из Pacman() по факту заполнения массива ключа
  //if(button1.flagClick==false)button2.flagClick = true;
}//END Pacman()
  //основной цикл отрисовки прилаги
   while(1)
  { ///Отрисовка графики плеера
 myOLED.clrScr();
 myOLED.drawRoundRect(1, 26, 127, 63);//граница основного инфо-поля 
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);//кнопка стрелка
  myOLED.drawRoundRect(1, 0, 17, 13);// квадраты отрисовки кнопок
  myOLED.drawRoundRect(110, 0, 127, 13);///-//-
  myOLED.print("<RFID_app>", CENTER, 2);
  myOLED.print("Save", 104, 15);
  myOLED.print("Exit", 1, 15);
 myOLED.print("NEW", CENTER, 28);//Заголовок -первая строка
 myOLED.print("Key Detected:)", CENTER, 37);//Заголовок -вторая строка
 myOLED.print("HEX", 6, 46);//
 for()
 myOLED.printNumI(,60,46);
 myOLED.print("DEC", 6, 54);//
 myOLED.drawLine( 28,46, 28,62);//крест разделения полей HEX/DEC
 myOLED.drawLine( 6,53, 122,53);//-//-
 //myOLED.drawRoundRect(8, 44, 121, 53);//Отрисовка шкалы процесинга проигрывателя
 myOLED.update();
    }
    if ( button2.flagClick == true ){button2.flagClick = false;
         //myOLED.setFont(SmallFont);
         if(!ts){ ts=!ts/*1*/;//BOOL on/off
                 myOLED.print("  ", 112, 4);// стирачка для галочки:)
                 myOLED.print("  ", 114, 4);// стирачка для галочки:)
                 myOLED.print("  ", 112, 2);// стирачка для галочки:)
                 myOLED.print("  ", 114, 2);// стирачка для галочки:)
                 myOLED.drawRect(114,2, 117,11);//вертикальные полоски для кнопки пауза
                 myOLED.drawRect(120,2, 123,11);//вертикальные полоски для кнопки пауза
                 myOLED.print("Stop", 104, 15);
                     }
                    else {ts=!ts/*0*/;//BOOL on/off
                    myOLED.print("  ", 112, 4);//стирачка для галочки:)
                    myOLED.print("  ", 114, 4);//стирачка для галочки:)
                    myOLED.print("  ", 112, 2);// стирачка для галочки:)
                 myOLED.print("  ", 114, 2);// стирачка для галочки:)
                    myOLED.drawLine( 116,3, 122,7);// треугольник для кнопки плей
                    myOLED.drawLine( 116,11,122,7);// -/-
                    myOLED.drawLine( 116,3,116,11);// -/-
                    myOLED.print("Play", 104, 15); 
                    }
       }
    if ( button1.flagClick == true ){// был клик кнопки 1
    //button1.flagClick = false;  // сброс признака
        noTone(Pin_tone);
        break;}
 myOLED.update();
 
  }
  
  digitalWrite( RDM6300_Pin, LOW);//выключаем rdm6300LOW
}
//////////
void readCard()
{ 
  if (rdm6300.available() > 0) 
  {    
    delay(100); 
    for (int i = 0 ; i < 14 ; i++) 
    {
      newCard[i] = rdm6300.read();      
      Serial.println(newCard[i]);
    }
    rdm6300.flush(); 
  }
}
/////// or?
// Arduino test sketch for http://arduino-ua.com/prod259-125Khz_RFID_modyl_RDM6300
#include <SoftwareSerial.h>
#define STX 2
#define ETX 3

SoftwareSerial softSerial(10, 11); // recommended pins for RX on Mega: 10, 11, 12...
int rx_counter;
byte rx_data[14]; // 1+10+2+1

void setup() {
  rx_counter = 0; // init counter
  Serial.begin(9600);
  softSerial.begin(9600);
}

void loop() {
  if (softSerial.available() > 0) {
    rx_data[rx_counter] = softSerial.read();
    if (rx_counter == 0 && rx_data[0] != STX) {
      Serial.println("Out of sync!"); // do not increment rx_counter
    } else {
      rx_counter++;
    }
    if (rx_counter >= 14) {
      rx_counter = 0; // reset counter
      if (rx_data[0] == STX && rx_data[13] == ETX) { // packet starts with STX and ends with ETX
        byte calc_checksum = 0;
        for (int i = 0; i < 6; i++) { // data with checksum
          calc_checksum ^= ascii_char_to_num(rx_data[i*2+1]) * 16 + ascii_char_to_num(rx_data[i*2+2]);
        }
        if (calc_checksum == 0) {
          Serial.print("ID: ");
          for (int i = 1; i <= 10; i++) {
            Serial.write(rx_data[i]);
          }
          Serial.println();
        } else {
          Serial.println("Checksum ERROR!");
        }
      } else {
          Serial.println("Incorrect packet!");
      }
    } 
  }
}

// convert a single hex character to its byte value using ASCII table (see https://ru.wikipedia.org/wiki/ASCII)
byte ascii_char_to_num(byte a) {
  a -= '0'; // 0..9
  if (a > 9) a -= 7; // A..F
  return a;
} 
