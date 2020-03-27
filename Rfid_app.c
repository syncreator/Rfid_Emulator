#include <SoftwareSerial.h>
#define RDM6300_PIN    9   // светодиод подключен к выводу 9 ????

SoftwareSerial RfidReader(0, 1);
int num;
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
/////// Еще вариант
void rdm6300_read(OLED &myOLED, Button &button1, Button &button2, byte m, byte RDM6300_Pin)
{ digitalWrite( RDM6300_Pin,  HIGH);//Включаем rdm6300
  wait(2000);//ждем пока включиться
  Pacman()//Запускаем Pacman пока rdm6300 не выдаст 14 битов?
  //основной цикл отрисовки прилаги
   while(1)
  { ///Отрисовка графики плеера
 myOLED.clrScr();
 myOLED.drawRoundRect(1, 26, 127, 63);
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);//кнопка стрелка
 myOLED.drawLine( 116,3, 122,7);// треугольник для кнопки плей
  myOLED.drawLine( 116,11,122,7);// -/-
  myOLED.drawLine( 116,3,116,11);// -/-
  myOLED.drawRoundRect(1, 0, 17, 13);// квадраты отрисовки кнопок
  myOLED.drawRoundRect(110, 0, 127, 13);///-//-
  myOLED.print("<MUSIC_app>", CENTER, 2);
  myOLED.print("Play", 104, 15);
  myOLED.print("Exit", 1, 15);
 myOLED.print(melody_name,9,30 );//название мелодии
 myOLED.drawRoundRect(8, 44, 121, 53);//Отрисовка шкалы процесинга проигрывателя
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
