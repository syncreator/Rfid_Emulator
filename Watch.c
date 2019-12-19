#includ
//Возвращает время в минутах на текущий момент вызова (диапазон 24часа)
int Watch(unsigned int Start_Time=0, unsigned long X_Point=0,)
{ int static s(0);
  unsigned long static cur_time=millis();
  unsigned long Temp_time; //переменная для промежуточных вычислений 
    Temp_time=Start_Time+(((cur_time-X_Point)/1000/60)%1440);//текущее время в минутах
  
 if((millis()>= X_Point)Temp_time=(((millis()-X_Point)/1000/60)%1440>=1440-Start_Time)?Start_Time+((millis()-X_Point)/1000/60)%1440:(((millis()-X_Point)/1000/60)%1440)-(1440-Start_Time);
    else )Temp_time=(((millis()-X_Point)/1000/60)%1440>=1440-Start_Time)?Start_Time+((millis()-X_Point)/1000/60)%1440:(((millis()-X_Point)/1000/60)%1440)-(1440-Start_Time);
 
 
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
