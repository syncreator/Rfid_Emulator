#include <avr/pgmspace.h>
#include <Arduino.h>
#include <OLED_I2C.h>
#include <Button.h>
//#include <SoftwareSerial.h>
#define RDM6300_PIN    13   //

extern uint8_t SmallFont[];
//extern uint8_t BigNumbers[];
//extern uint8_t MediumNumbers[];
extern uint8_t arrow_13x10[];
extern uint8_t check_14x10[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];

byte ascii_num(byte a);

//extern void destr(byte i, int x);
//extern int constr(byte i);

/////// Прилага для считывания rfid ключей
void rdm6300_read(OLED &myOLED, volatile Button &button1, volatile Button &button2,/* SoftwareSerial &RfidReader,*/ /*byte m,*/ byte RDM6300_Pin)
{ 
  uint8_t* bm;
  int pacy;
  byte num[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  //Serial.begin(9600);
  while(1){
  //begin://метка goto
  //int count(0);//?это надо?
 //byte num[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 //String s = "";
 //bool flag=false;
 digitalWrite( RDM6300_Pin,  HIGH);//Включаем rdm6300
  unsigned long x=millis();
 while((millis()-x)<100){if ( (button1.flagClick || button2.flagClick) == true )
 // был клик кнопки 1
        break;}//ждем пока включиться
Serial.begin(9600); //?????????
//RfidReader.begin(9600);
//RfidReader.flush();//очистка буфера
//////
  //Запускаем Pacman пока rdm6300 не выдаст 14 битов?
 { myOLED.clrScr();
  for (int pc = 0; pc < 3; pc++)
  {
    if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
        if (Serial/*RfidReader*/.available()>13)break;
    pacy = random(20, 44);
    //int j=0;
    for (int i = -20,j=0; i < 132; i++,j++)
    {
      if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
        if (Serial/*RfidReader*/.available()>13)break;
      myOLED.clrScr();
      for (int p = 6; p > ((i + 20) / 20); p--)
      {
        if ( button1.flagClick == true )
          // был клик кнопки 1
          break;
          if (Serial/*RfidReader*/.available() >13)break;
        if (random(0, 100) % 2)myOLED.print("0", p * 20 - 8, pacy + 7);
        else myOLED.print("1", p * 20 - 8, pacy + 7); //drawBitmap(p*20-8, pacy+7, "1", 5, 5);
      }
      if ( button1.flagClick == true )
        // был клик кнопки 1
        break;
        if (Serial/*RfidReader*/.available() > 13)break;
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
     if (Serial/*RfidReader*/.available() >13)break;
      //delay(10);
     //wait(int t)
     {unsigned long x=millis();
 while((millis()-x)<10/*t*/){if ( (button1.flagClick || button2.flagClick) == true )break;
        // был клик кнопки 1
 }
}//END wait()
    }
  }
}//END Pacman()
 //if (Serial/*RfidReader*/.available() > 0)
 //delay(100);
 digitalWrite( RDM6300_Pin, LOW);//выключаем rdm6300LOW
 //-------------------------------
   bool flag_s = true;
   while(Serial.available())
   { if(Serial.peek()==2 && flag_s)
     {Serial.print("ID: ");
      for(int j=0; j<14; j++)
      {
      num[j]=Serial.read();
      Serial.print(num[j]);
      Serial.print(",");
      }
      //check sum test
      if (num[0] == 2 && num[13] == 3) // packet starts with STX and ends with ETX
        {
           byte checksum = 0;
        for (int i = 0; i < 6; i++) { // data with checksum
          checksum ^= ascii_num(num[i*2+1]) * 16 + ascii_num(num[i*2+2]);
        }
        if (checksum == 0)
        { flag_s=!flag_s;
          Serial.println("Checksum OK!");
          Serial.print("ID: ");
          for (int i = 1; i <= 10; i++) {
            Serial.print(num[i],DEC);
          }
          Serial.println();
        } 
        else 
         {
          Serial.println("Checksum ERROR!");
         }
       }
      else Serial.println("Key ERROR!");
     }
     else Serial.read();
       
   }
   // {{unsigned long x=millis();
// while((millis()-x)<10/*t*/){}};//???
//---------------------
for(int i=1,j=0;i<N;)//N-quantity Key in Menu
{
    if(EEPROM[30*i+j]==num[i])j++;
    else i++;
    if(j>10)std::cout << "Already saved as:" <<i<< std::endl;
}
//------------------------   
   ///Отрисовка графики прилаги
 myOLED.clrScr();
 myOLED.drawRoundRect(1, 24, 127, 63);//граница основного инфо-поля 
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);//кнопка стрелка
 myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
  myOLED.drawRoundRect(1, 0, 17, 13);// квадраты отрисовки кнопок
  myOLED.drawRoundRect(110, 0, 127, 13);///-//-
  myOLED.print("<RFID_app>", CENTER, 2);
  myOLED.print("Save", 104, 15);
  myOLED.print("Exit", 1, 15);
 myOLED.print("NEW", CENTER, 26);//Заголовок -первая строка
 myOLED.print("Key Detected:)", CENTER, 34);//Заголовок -вторая строка
 myOLED.print("HEX", 4, 44);//
 for(byte i=1;i<11;i++)myOLED.printNumI((char)num[i],28+7*i,44);
 myOLED.print("DEC", 4, 54);//
 for(byte i=1;i<11;i++)myOLED.printNumI((char)num[i],28+7*i,54);
 myOLED.drawLine( 26,46, 26,62);//крест разделения полей HEX/DEC
 myOLED.drawLine( 6,52, 122,52);//-//-
 //myOLED.drawRoundRect(8, 44, 121, 53);//Отрисовка шкалы процесинга проигрывателя
 myOLED.update();
 //digitalWrite( RDM6300_Pin, LOW);//выключаем rdm6300LOW
 //delay(500);
  while(1/*!button2.flagClick*/)//проверка нажатия кнопок
    {if ( button2.flagClick == true ){button2.flagClick = false;
         //myOLED.setFont(SmallFont);
        //переходим на начало
                 //myOLED.print("Try else", 80, 15);
                 break;
                // goto begin;
                     }
    if ( button1.flagClick == true ){// был клик кнопки 1
    button1.flagClick = false;  // сброс признака, ОБЯЗАТЕЛЬНОЕ!!! условие выхода из цикла
      //  break;}
      }
// myOLED.update();
 
   }//END While(1)
}//END Main While!!!
  //выключаем RDM6300
  //digitalWrite( RDM6300_Pin, LOW);//выключаем rdm6300LOW
}
///////
// convert a single hex character to its byte value using ASCII table
byte ascii_num(byte a) {
  a -= '0'; // 0..9
  if (a > 9) a -= 7; // A..F
  return a;
}
