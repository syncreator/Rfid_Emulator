#include <Arduino.h>
#include <OLED_I2C.h>
#include <Button.h>

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t arrow_13x10[];
extern uint8_t check_14x10[];
extern void destr(byte i, int x);
extern int constr(byte i);

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

void Watch(OLED &myOLED, Button &button1, Button &button2, uint8_t* bm, byte Pin_tone, unsigned long St_time=0, unsigned long X_point=0, unsigned int alarm_time=0, int alarm_flag=0)//вывод часов на весь экран + будильник
{unsigned long  prevTime=Time(St_time,X_point);
 byte g(0),j(0);
 boolean p=true;
 //Заголовок + инфа по будильнику и обрамление
 myOLED.clrScr();
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
 //myOLED.drawBitmap(112, 2, bm, 14, 10);///
  myOLED.drawRoundRect(1, 0, 17, 13);
  myOLED.drawRoundRect(110, 0, 127, 13);///
 //myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Watch_app>", CENTER, 2);
 myOLED.print("ALARM ->",5,19 );
  //myOLED.drawBitmap(62,18, bm, 15, 14);
 if(alarm_flag){ myOLED.print(" _ON", 58, 19);//BOOL on/off
                       myOLED.drawBitmap(112, 2, bm, 14, 10);
                     }
                    else {myOLED.print("_OFF", 58, 19);
                    }
 myOLED.printNumI(alarm_time/60, 92, 19, 2,'0');//Т_2
                    myOLED.print(":",105,19);
                    myOLED.printNumI(alarm_time%60, 110, 19, 2,'0');
  myOLED.drawRoundRect(1, 15, 127, 29);
  myOLED.drawRoundRect(1, 31, 127, 63);
 //
 myOLED.drawRoundRect(40, 40, 45, 46);//точки между часами/минутами
 myOLED.drawRoundRect(40, 50, 45, 56);
 /*myOLED.drawCircle(42,43,3);
 myOLED.drawCircle(42,53,3);*/
 ///////
 myOLED.drawRoundRect(82, 40, 87, 46);//точки между минутами/секундами
 myOLED.drawRoundRect(82, 50, 87, 56);
 /*myOLED.drawCircle(82,43,3);
 myOLED.drawCircle(82,53,3);*/
 //////////////////////////////////

  while(1)
  {if ( button2.flagClick == true ){button2.flagClick = false;
         destr(5,!constr(5));myOLED.setFont(SmallFont);
         if(constr(5)){ myOLED.print(" _ON ", 58, 19);//BOOL on/off
                       myOLED.drawBitmap(112, 2, bm, 14, 10);
                     }
                    else {myOLED.print("_OFF", 58, 19);
                    myOLED.print("  ", 112, 3);
                    myOLED.print("  ", 113, 1);
                    }
       }
    if ( button1.flagClick == true ){// был клик кнопки 1
    //button1.flagClick = false;  // сброс признака
        myOLED.setFont(SmallFont);
        break;}
    ////////////// Будильник
    if(j)
    {if(g>8){g=0;j--;}
    if(!g){tone(Pin_tone, 3520); delay(100);}
    if(g==1){tone(Pin_tone, 3136); delay(100);}
    if(g==2){tone(Pin_tone, 2637); delay(100);} 
    if(g==3){tone(Pin_tone, 2093); delay(100);}  
    if(g==4){tone(Pin_tone, 2349); delay(100);} 
    if(g==5){tone(Pin_tone, 3951); delay(100);} 
    if(g==6){tone(Pin_tone, 2794); delay(100);} 
    if(g==7){tone(Pin_tone, 2093); delay(100);
    noTone(Pin_tone);}
            
    if(g==8){if(prevTime!=Time(St_time,X_point))g++;}//delay(500);
    else g++;
    if(constr(5))j=0;
    if(g%4)myOLED.invert(!p);//else myOLED.invert(false);
    }else if(constr(5) && prevTime==alarm_time)j=10;
    ///////
    if(prevTime!=Time(St_time,X_point)){prevTime=Time(St_time,X_point);
                          
                            ///////////////////////////////////////////////////////
                            
                             //myOLED.clrScr();
                             myOLED.setFont(BigNumbers);
                             myOLED.printNumI(prevTime/60/60, 8, 35,2,'0'); //часы
                             
                             //myOLED.print(".", 36, 27);
                             myOLED.printNumI((prevTime/60)%60, 50, 35,2,'0');//минуты
                            
                             //myOLED.print(".", 78, 27);
                             myOLED.printNumI(prevTime%60,92 ,35,2,'0');//секунды
                             myOLED.update();
    }
  }
}
