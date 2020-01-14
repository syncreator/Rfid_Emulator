#include <Arduino.h>

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

void Watch(unsigned long St_time=0, unsigned long X_point=0, unsigned int alarm_time=0, int alarm_flag=0)//вывод часов на весь экран + будильник
{unsigned long  prevTime=Time(St_time,X_point);
 //Заголовок + инфа по будильнику и обрамление
 myOLED.clrScr();
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);
 //myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
  myOLED.drawRoundRect(1, 0, 17, 13);
 //myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<Watch_app>", CENTER, 0);
 myOLED.print("ALARM",3, 14);
 if(alarm_flag) myOLED.print("on", 35, 14);//BOOL on/off
                    else myOLED.print("off", 35, 14);
 myOLED.printNumI(alarm_time/60, 65, 14, 2,'0');//Т_2
                    myOLED.print(":", 75,  14, 2,'0');
                    myOLED.printNumI(alarm_time%60, 82, 14, 2,'0');
  myOLED.drawRoundRect(1, 6, 127, 16);
  myOLED.drawRoundRect(1, 18, 127, 63);
 //
 for (int i=0; i<=10000; i++)
  {
    myOLED.setFont(MediumNumbers);
    myOLED.printNumF(float(i)/3, 2, RIGHT, 0);
    myOLED.setFont(BigNumbers);
    myOLED.printNumI(i, RIGHT, 40);
    myOLED.update();
  }
  myOLED.setFont(SmallFont);
  
  //////////////////////////////////

  while(1)
  {if ( button1.flagClick == true )
        // был клик кнопки 1
        myOLED.setFont(SmallFont);
        break;
    if(prevTime!=Time(St_time,X_point){prevTime=Time(St_time,X_point);
                           /* myOLED.clrScr();
                            myOLED.print("Time",5, 2);
                            myOLED.printNumI(Time(constr(3),constr(9)*65535+constr(10)), 30, 2);
                            myOLED.print("ST_time*60", 15, 11);
                            myOLED.printNumI(t, 5, 21);
                            myOLED.printNumI(t*60,40,21,5);
                            myOLED.print("X_point", 15, 32);
                            myOLED.printNumI(constr(9)*65535+constr(10), 15, 42,10);*/
                            ///////////////////////////////////////////////////////
                             myOLED.printNumI(prevTime/60/60, 74, 57,2,'0'); //часы
                             myOLED.print(":", 87, 57);
                             myOLED.printNumI((prevTime/60)%60, 92, 57,2,'0');//минуты
                             myOLED.print(":", 105, 57);
                             myOLED.printNumI(prevTime%60, 110, 57,2,'0');//секунды
                             myOLED.update();
                              myOLED.clrScr();
                              myOLED.printNumI(9/*prevTime/60/60*//*, 8, 27,2,'0'); //часы
                            /* myOLED.print(".", 36, 27);
                             myOLED.printNumI((prevTime/60)%60, 50, 27,2,'0');//минуты
                             myOLED.print(".", 78, 27);
                             myOLED.printNumI(prevTime%60,92 ,27,2,'0');//секунды
                             myOLED.update();
       }
    }*/
}
