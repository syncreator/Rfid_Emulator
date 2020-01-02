#includ
//Возвращает время в минутах на текущий момент вызова (диапазон 24часа)
int Watch(unsigned int St_time=0, unsigned long X_point=0,)//St_time точка отчета времени установленная юзером в конфиге, X_point значение временни по millis() синхронизированное c моментом установки времени в конфиге:)  
{ int static s(0);//переменная для вычисления четности момента мигания секундных точек
  unsigned long static cur_time=millis();//флаг для определения истечения какого-то промежутка времени
  unsigned long Temp_time; //переменная для промежуточных вычислений 
    //Temp_time=St_time+(((cur_time-X_Point)/1000/60)%1440);//текущее время в минутах
  
 if((millis()>= X_point)Temp_time=(((millis()-X_Point)/1000)%86400>=(1440-Start_Time)*60)?((millis()-X_Point)/1000)%86400-(1440-Start_Time)*60:Start_Time*60+((millis()-X_Point)/1000)%86400;
    else Temp_time=(((X_Point-millis())/1000)%86400>=Start_Time*60)?Start_Time*60+(86400-((X_Point-millis())/1000)%86400): Start_Time*60-(X_Point-millis())/1000%86400;
 //Temp_time=(St_time>=(X_point-millis())%1440)? St_time-(X_point-millis())%1440 : St_time+(1440-(X_point-millis())%1440);
 
    if(cur_time+1000<=millis())
    { cur_time=millis();s++;
     if(!_Menu)
      { myOLED.drawRoundRect(90, 15, 127, 26);//?стирачка??????
        myOLED.update();
        myOLED.printNumI(Temp-time/60,40, 57);//Вывод в граф меню часы
        myOLED.printNumI(Temp-time%60,50, 57);//Вывод в граф меню минуты
       if(s%2)myOLED.print(":", 106,57);else myOLED.print(" ", 106,57);//мигалка точечками
        myOLED.update();
      }
    }else if(cur_time>millis())cur_time=millis();//перестраховка на случай переполнения и сброса millis()
  //cur_time=millis();
     if(cur_time>millis())
 
}
