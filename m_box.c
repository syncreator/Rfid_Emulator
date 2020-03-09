#include <avr/pgmspace.h>
#include <Arduino.h>
#include <OLED_I2C.h>
#include <Button.h>

//Структура мелодии
struct MUSIC{
  int note;
  uint8_t dur;
};
//Мелодии:
static const MUSIC ST_WARS[]PROGMEM = {
   392, 350, //0
   392, 350, //1
   392, 350, //2
   311, 250, //3
   466, 100, //4
   392, 350, //5
   311, 250, //6
   466, 100, //7
   392, 700, //8
   587, 350, //9
   587, 350, //10
   587, 350, //11
   622, 250, //12
   466, 100, //13
   369, 350, //14
   311, 250, //15
   466, 100, //16
   392, 700, //17
   784, 350, //18
   392, 250, //19
   392, 100, //20
   784, 350, //21
   739, 250, //22
   698, 100, //23
   659, 100, //24
   622, 100, //25
   659, 450, //26
   415, 150, //27
   554, 350, //28
   523, 250, //29
   493, 100, //30
   466, 100, //31
   440, 100, //32
   466, 450, //33
   311, 150, //34
   369, 350, //35
   311, 250, //36
   466, 100, //37
   392, 750, //38
   0,0,
};
//Nokia_tune
static const MUSIC NOK_TUNE[]PROGMEM = {
  NOTE_E5, 1000/8, //0
  NOTE_D5, 1000/8, //1
  NOTE_F4, 1000/4, //2
  NOTE_G4, 1000/4, //3
  NOTE_C5, 1000/8, //4
  NOTE_B4, 1000/8, //5
  NOTE_D4, 1000/4, //6
  NOTE_E4, 1000/4, //7
  NOTE_B4, 1000/8, //8
  NOTE_A4, 1000/8, //9
  NOTE_C4, 1000/4, //10
  NOTE_E4, 1000/4, //11
  NOTE_A4, 1000/1, //12
  0,0,
};
//Pacman_#1
static const MUSIC PACMAN_1[]PROGMEM = {
  NOTE_B5, 1000/6, //0
  NOTE_B6, 1000/6, //1
  NOTE_FS6, 1000/6, //2
  NOTE_DS6, 1000/6, //3
  NOTE_B6, 1000/6, //4
  NOTE_F6, 1000/6, //5
  NOTE_E6, 1000/6, //6
  NOTE_C5, 1000/6, //7
  NOTE_C6, 1000/6, //8
  NOTE_G6, 1000/6, //9
  NOTE_F5, 1000/6, //10
  NOTE_C6, 1000/6, //11
  NOTE_G6, 1000/6, //12 
  NOTE_E6, 1000/6, //13
  0,0,
};
//Pacman_#2
static const MUSIC PACMAN_2[]PROGMEM = {
  NOTE_B4, 1000/16, //0
  NOTE_B5, 1000/16, //1
  NOTE_FS5, 1000/16, //2 
  NOTE_DS5, 1000/16, //3
  NOTE_B5, 1000/32, //4
  NOTE_FS5, 1000/16, //5
  NOTE_DS5, 1000/8, //6
  NOTE_C5, 1000/16, //7
  NOTE_C6, 1000/16, //8
  NOTE_G6, 1000/16, //9
  NOTE_E6, 1000/16, //10 
  NOTE_C6, 1000/32, //11
  NOTE_G6, 1000/16, //12 
  NOTE_E6, 1000/8, //13
  NOTE_B4, 1000/16, //14
  NOTE_B5, 1000/16, //15
  NOTE_FS5, 1000/16, //16
  NOTE_DS5, 1000/16, //17
  NOTE_B5, 1000/32, //18
  NOTE_FS5, 1000/16, //19
  NOTE_DS5, 1000/8, //20
  NOTE_DS5, 1000/32, //21
  NOTE_E5, 1000/32, //22
  NOTE_F5, 1000/32, //23
  NOTE_F5, 1000/32, //24
  NOTE_FS5, 1000/32, //25
  NOTE_G5, 1000/32, //26
  NOTE_G5, 1000/32, //27
  NOTE_GS5, 1000/32, //28
  NOTE_A5, 1000/16, //29
  NOTE_B5, 1000/8, //30
  0,0,
};
//Crocodil_Gena
static const MUSIC C_GENA[]PROGMEM = {
  330, 200, //0
  439, 200, //1
  414, 200, //2
  439, 200, //3
  493, 200, //4
  439, 200, //5
  391, 200, //6
  439, 200, //7
  391, 400, //8
  349, 400, //9
  348, 600, //10
  32767, 200, //11
  293, 200, //12
  391, 200, //13
  369, 200, //14
  391, 200, //15
  439, 200, //16
  391, 200, //17
  293, 200, //18
  348, 200, //19
  329, 600, //20
  32767, 600, //21
  329, 200, //22
  439, 200, //23
  414, 200, //24
  439, 200, //25
  493, 200, //26
  439, 200, //27
  391, 200, //28
  348, 200, //29
  329, 400, //30
  293, 400, //31
  439, 600, //32
  32767, 200, //33
  329, 200, //34
  523, 200, //35
  493, 200, //36
  439, 200, //37
  414, 200, //38
  439, 200, //39
  493, 200, //40
  414, 200, //41
  439, 600, //42
  32767, 600, //43
  0,0,
};

void Music(byte m, byte Pin_tone, char* melody_name))//номер мелодии, указатель на название мелодии
{ MUSIC *bm ;
   bool ts(0);//переменная для включения/выключения паузы в плеере
   int n(0),m(0);//для расчета кол-ва нот в массиве
   float s;//расчет статуса проигрыша мелодии
   unsigned long x;
  if(m==5)
 {/// звуки для оформления
    // звук "Успешное включение"
    tone(Pin_tone, NOTE_A7); delay(100);
    tone(Pin_tone, NOTE_G7); delay(100);
    tone(Pin_tone, NOTE_E7); delay(100); 
    tone(Pin_tone, NOTE_C7); delay(100);  
    tone(Pin_tone, NOTE_D7); delay(100); 
    tone(Pin_tone, NOTE_B7); delay(100); 
    tone(Pin_tone, NOTE_F7); delay(100); 
    tone(Pin_tone, NOTE_C7); delay(100);
    noTone(Pin_tone); 
    delay(2000);
    
// звук ОК
    for (int i=400; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(20); }
    noTone(Pin_tone);
    delay(2000);
  
// звук "очередной шаг"
    for (int i=2500; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(10); }
    noTone(Pin_tone);
    delay(2000);
  
// звук "ERROR"
    for (int j=0; j <3; j++){
    for (int i=1000; i<2000; i=i*1.1) { tone(Pin_tone, i); delay(10); }
    delay(50);
    for (int i=1000; i>500; i=i*1.9) { tone(Pin_tone, i); delay(10); }
    delay(50);
    }
    noTone(Pin_tone);
    delay(2000);
 //Звук Laser??
 for (int i = 5; i>1; i--) {
      for (int j = 3; j > 0; j--) {
        //analogWrite(ledPin, i*25);
        tone(Pin_tone, round((j*i)*(100/4)), 50);
        delay(50/10);
      }
      tone(Pin_tone, round((i)*(100/4)), 50);
    }
   noTone(Pin_tone);
}//if end
  else{switch (m)
      {
        case 0: {bm = ST_WARS; while((uint8_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm = ST_WARS;}
          break;
        case 1: {bm = NOK_TUNE; while((uint8_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm = NOK_TUNE;}
          break;
        case 2: {bm = PACMAN_1; while((uint8_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm = PACMAN_1;}
          break;
        case 3: {bm = PACMAN_2; while((uint8_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm = PACMAN_2;}
          break;
        case 4: {bm = C_GENA; while((uint8_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm = C_GENA;}
          break;
      }
     }
 s= (float)(110.0/(n-1));//вычисляем шаг в пикселях на шкале отрисовки сыгранных нот
 ///Отрисовка графики плеера
 myOLED.clrScr();
 myOLED.drawBitmap(3, 2, arrow_13x10, 13, 10);//кнопка стрелка
 //myOLED.drawBitmap(112, 2, check_14x10, 14, 10);///
 //myOLED.print("  ", 112, 3);// стирачка для галочки:)
 //myOLED.print("  ", 113, 1); // стирачка для галочки:)
  myOLED.drawRect(3, 115, 11, 118);//вертикальные полоски для кнопки пауза
  myOLED.drawRect(3, 120, 11, 123);//вертикальные полоски для кнопки пауза
  myOLED.drawRoundRect(1, 0, 17, 13);// квадраты отрисовки кнопок
  myOLED.drawRoundRect(110, 0, 127, 13);///-//-
 //myOLED.drawRoundRect(110, 0, 127, 13);
  myOLED.print("<MUSIC_app>", CENTER, 2);
 myOLED.print(melody_name,5,19 );//название мелодии
 myOLED.drawRoundRect(9, 38, 119, 55);//Отрисовка шкалы процесинга проигрывателя
  //myOLED.drawBitmap(62,18, bm, 15, 14);
 /*if(alarm_flag){ myOLED.print("_ON", 62, 19);//BOOL on/off
                       myOLED.drawBitmap(112, 2, bm, 14, 10);
                     }
                    else {myOLED.print("_OFF", 62, 19);
                    }
 myOLED.printNumI(alarm_time/60, 92, 19, 2,'0');//Т_2
                    myOLED.print(":",105,19);
                    myOLED.printNumI(alarm_time%60, 110, 19, 2,'0');
  myOLED.drawRoundRect(1, 15, 127, 29);
  myOLED.drawRoundRect(1, 31, 127, 63);*/
 //
 /*myOLED.drawRoundRect(40, 40, 45, 46);//точки между часами/минутами
 myOLED.drawRoundRect(40, 50, 45, 56);
 /*myOLED.drawCircle(42,43,3);
 myOLED.drawCircle(42,53,3);
 ///////
 myOLED.drawRoundRect(82, 40, 87, 46);//точки между минутами/секундами
 myOLED.drawRoundRect(82, 50, 87, 56);*/
 //////////////////////////////////
 

  while(1)//Ожидание нажатия кнопок
  {if ( button2.flagClick == true ){button2.flagClick = false;
         //myOLED.setFont(SmallFont);
         if(!ts){ ts==!ts;//BOOL on/off
                 myOLED.print("  ", 112, 3);// стирачка для галочки:)
                 myOLED.print("  ", 113, 1);// стирачка для галочки:)
                 myOLED.drawLine(3, 115, 7, 118);// треуголбник для кнопки плей
                 myOLED.drawLine(11, 115, 7, 118);// -/-
                 myOLED.drawLine(3, 115, 11, 115);// -/-
                       //myOLED.drawBitmap(112, 2, check_14x10, 14, 10);
                     }
                    else {ts==!ts;//BOOL on/off
                    myOLED.print("  ", 112, 3);//стирачка для галочки:)
                    myOLED.print("  ", 113, 1);//стирачка для галочки:)
                    myOLED.drawRect(3, 115, 11, 118);//вертикальные полоски для кнопки пауза
                    myOLED.drawRect(3, 120, 11, 123);//вертикальные полоски для кнопки пауза  
                    }
       }
    if ( button1.flagClick == true ){// был клик кнопки 1
    //button1.flagClick = false;  // сброс признака
        noTone(Pin_tone);
        break;}
   myOLED.update();
 
///////////////////////////////////////// 
 
/* if(m==5)
 {/// звуки для оформления
    // звук "Успешное включение"
    tone(Pin_tone, NOTE_A7); delay(100);
    tone(Pin_tone, NOTE_G7); delay(100);
    tone(Pin_tone, NOTE_E7); delay(100); 
    tone(Pin_tone, NOTE_C7); delay(100);  
    tone(Pin_tone, NOTE_D7); delay(100); 
    tone(Pin_tone, NOTE_B7); delay(100); 
    tone(Pin_tone, NOTE_F7); delay(100); 
    tone(Pin_tone, NOTE_C7); delay(100);
    noTone(Pin_tone); 
    delay(2000);
    
// звук ОК
    for (int i=400; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(20); }
    noTone(Pin_tone);
    delay(2000);
  
// звук "очередной шаг"
    for (int i=2500; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(10); }
    noTone(Pin_tone);
    delay(2000);
  
// звук "ERROR"
    for (int j=0; j <3; j++){
    for (int i=1000; i<2000; i=i*1.1) { tone(Pin_tone, i); delay(10); }
    delay(50);
    for (int i=1000; i>500; i=i*1.9) { tone(Pin_tone, i); delay(10); }
    delay(50);
    }
    noTone(Pin_tone);
    delay(2000);
 //Звук Laser??
 for (int i = 5; i>1; i--) {
      for (int j = 3; j > 0; j--) {
        //analogWrite(ledPin, i*25);
        tone(Pin_tone, round((j*i)*(100/4)), 50);
        delay(50/10);
      }
      tone(Pin_tone, round((i)*(100/4)), 50);
    }
   noTone(Pin_tone);
}//if end*/
    if(ts && m<(n-2))//если в режиме PLAY и сыграны не все ноты
 //while(bm->note)
     {
      m++;
      myOLED.drawRoundRect(9, 40, 9+round(m*s), 53);
      myOLED.printNumI(round(m*s),15,56,3,'0');
      myOLED.print("%", 40, 56);
      myOLED.update();
    tone(Pin_tone, bx->note, bm->dur);
    //digitalWrite(13, HIGH);
    //delay(bm->dur);
      //начало блока вызова цикла задержки аналог delay()
    { x=millis();
      while((millis()-x)<(bm->dur)){if ( (button1.flagClick || button2.flagClick) == true )
        // был клик кнопки 1
        break;}
    }
    //digitalWrite(13, LOW);
    //delay(pauseBetweenNotes/2);
  }
  else noTone(Pin_tone);
    }//else end

}
