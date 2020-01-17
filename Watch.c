#include <Arduino.h>
#include <OLED_I2C.h>
#include <Button.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t arrow_13x10[];

//extern uint8_t check_14x10[];
/*namespace ns {
extern OLED  myOLED(SDA, SCL, 8);
extern Button button1(BUTTON_1_PIN, 0);
}
using namespace ns;*/

unsigned long Time(unsigned long St_time=0, unsigned long X_point=0/*,unsigned long M*/)//St_time точка отчета времени установленная юзером в конфиге, X_point значение временни по millis() синхронизированное c моментом установки времени в конфиге:)  
{ //int static s(0);//переменная для вычисления четности момента мигания секундных точек
  //unsigned long static cur_time=millis();//флаг для определения истечения какого-то промежутка времени
  unsigned long Temp_time=0;//переменная для промежуточных вычислений 
  unsigned long Tm=millis();
  
 if(Tm>= X_point)Temp_time=(((Tm-X_point)/1000)%86400>=(1440-St_time)*60)?((Tm-X_point)/1000)%86400-(1440-St_time)*60:St_time*60+((Tm-X_point)/1000)%86400;
    else Temp_time=(((X_point-Tm)/1000)%86400>=St_time*60)?St_time*60+(86400-((X_point-Tm)/1000)%86400): St_time*60-(X_point-Tm)/1000%86400;
 
 return Temp_time;
}
///////////////////////////////////////////

void Watch(OLED &myOLED, Button &button1, Button &button2, uint8_t* bm, unsigned long St_time=0, unsigned long X_point=0, unsigned int alarm_time=0, int alarm_flag=0)//вывод часов на весь экран + будильник
{unsigned long  prevTime=Time(St_time,X_point);
 //Заголовок + инфа по будильнику и обрамление
 myOLED.clrScr();
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
 myOLED.drawBitmap(112, 0, bm, 8, 8);
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
  myOLED.drawRoundRect(1, 15, 127, 29);
  myOLED.drawRoundRect(1, 31, 127, 63);
 //
 /*myOLED.drawRoundRect(40, 40, 45, 46);//точки между часами/минутами
 myOLED.drawRoundRect(40, 50, 45, 56);*/
 myOLED.drawCircle(42,43,3);
 myOLED.drawCircle(42,53,3);
 ///////
 /*myOLED.drawRoundRect(82, 40, 87, 46);//точки между минутами/секундами
 myOLED.drawRoundRect(82, 50, 87, 56);*/
 myOLED.drawCircle(82,43,3);
 myOLED.drawCircle(82,53,3);
 ///////
  /*myOLED.drawRoundRect(1, 31, 42, 63);// обрамление часы/минуты/секунды
  myOLED.drawRoundRect(44, 31, 85, 63);
  myOLED.drawRoundRect(87, 31, 127, 63);*/
 /*for (int i=0; i<=10000; i++)
  {
    myOLED.setFont(MediumNumbers);
    myOLED.printNumF(float(i)/3, 2, RIGHT, 0);
    myOLED.setFont(BigNumbers);
    myOLED.printNumI(i, RIGHT, 40);
    myOLED.update();
  }
  myOLED.setFont(SmallFont);*/
  
  //////////////////////////////////

  while(1)
  {if ( button2.flagClick == true )button2.flagClick = false;
    if ( button1.flagClick == true ){// был клик кнопки 1
    //button1.flagClick = false;  // сброс признака
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
                            /* myOLED.printNumI(prevTime/60/60, 74, 57,2,'0'); //часы
                             myOLED.print(":", 87, 57);
                             myOLED.printNumI((prevTime/60)%60, 92, 57,2,'0');//минуты
                             myOLED.print(":", 105, 57);
                             myOLED.printNumI(prevTime%60, 110, 57,2,'0');//секунды
                             myOLED.update();*/
                             //myOLED.clrScr();
                             myOLED.setFont(BigNumbers);
                             myOLED.printNumI(prevTime/60/60, 8, 35,2,'0'); //часы
                             /*myOLED.drawRoundRect(36, 40, 38, 46);
                             myOLED.drawRoundRect(36, 50, 38, 56);*/
                             //myOLED.print(".", 36, 27);
                             myOLED.printNumI((prevTime/60)%60, 50, 35,2,'0');//минуты
                             /*myOLED.drawRoundRect(78, 40, 80, 46);
                             myOLED.drawRoundRect(78, 50, 80, 56);*/
                             //myOLED.print(".", 78, 27);
                             myOLED.printNumI(prevTime%60,92 ,35,2,'0');//секунды
                             myOLED.update();
    }
  }
}
