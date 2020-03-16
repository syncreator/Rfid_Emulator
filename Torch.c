int led_pin_red1 = 5; // пин подключения светика red1
int led_pin_red2 = 5; // пин подключения светика red2
int led_pin_green1 = 5; // пин подключения светика green1
int led_pin_green2 = 5; // пин подключения светика green2
int led_pin_blue1 = 5; // пин подключения светика blue1
int led_pin_blue2 = 5; // пин подключения светика blue2
////
boolean status = true; // флаг, что активна левая
boolean open = true; // флаг, включения
/////////////
void setup()
    {
pinMode( led_pin_red1,  OUTPUT);
pinMode( led_pin_red2,  OUTPUT);
pinMode( led_pin_green1,  OUTPUT);
pinMode( led_pin_green2,  OUTPUT);
pinMode( led_pin_blue1,  OUTPUT);
pinMode( led_pin_blue2,  OUTPUT);
    }
//////
........
 byte del(0);//период мерцания
  while(1)
  {if ( button2.flagClick == true ){button2.flagClick = false;
          if(del>10)del=0;else del++;}
    if(constr(red))
    {digitalWrite( led_pin_red1, HIGH);
     digitalWrite( led_pin_red2, HIGH);
    };
   if(constr(green))
    {digitalWrite( led_pin_green1,  HIGH);
     digitalWrite( led_pin_green2,  HIGH);
    };
   if(constr(blue))
    {digitalWrite( led_pin_blue1,  HIGH);
     digitalWrite( led_pin_blue2,  HIGH);
    };   
   if(del)//проверка на 
     {wait(del*50));//меняем частоту мерцания
     digitalWrite( led_pin_red1, LOW);
     digitalWrite( led_pin_red2, LOW);
     digitalWrite( led_pin_green1, LOW);
     digitalWrite( led_pin_green2, LOW);
     digitalWrite( led_pin_blue1, LOW);
     digitalWrite( led_pin_blue2, LOW);
     }
    if ( button1.flagClick == true ){// был клик кнопки 1
      //button1.flagClick = false;  // сброс признака
     digitalWrite( led_pin_red1, LOW);
     digitalWrite( led_pin_red2, LOW);
     digitalWrite( led_pin_green1, LOW);
     digitalWrite( led_pin_green2, LOW);
     digitalWrite( led_pin_blue1, LOW);
     digitalWrite( led_pin_blue2, LOW);
        break;}
  }
////
////-Полицейская мигалка поочереди двумя диодами
for (int x=0; x<6; x++) { // цикл 6 проходов
    if (open) // если true
        digitalWrite(status ? led_3 : led_5, HIGH); // если status == false то падаем на пин 3 иначе на пин 5
    else // иначе
      digitalWrite(status ? led_3 : led_5, LOW); // если status == false то падаем на пин 3 иначе на пин 5
    delay(interval[x]); // Ждем 
     if (x == 5) // если последний проход по циклу
        status = !status; // передаем слово (меняем текущий пин) меняем false на true и наоборот;
    open = !open; //меняем false на true и наоборот;
   }                      
