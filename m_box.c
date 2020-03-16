#include <avr/pgmspace.h>
#include <Arduino.h>
#include <OLED_I2C.h>
#include <Button.h>

#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

extern uint8_t SmallFont[];
//extern uint8_t BigNumbers[];
//extern uint8_t MediumNumbers[];
extern uint8_t arrow_13x10[];
//extern uint8_t check_14x10[];

//Структура мелодии
struct MUSIC{
  uint16_t note;
  uint16_t dur;
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

void Music(OLED &myOLED, Button &button1, Button &button2,byte m, byte Pin_tone, char* melody_name)//номер мелодии, указатель на название мелодии
{ MUSIC *bm;
   bool ts(0);//переменная для включения/выключения паузы в плеере
   int n(0),k(0);//для расчета кол-ва нот в массиве
   float s;//расчет статуса проигрыша мелодии
   unsigned long x;
  if(m==3)
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
    delay(1000);
    
// звук ОК
   /* for (int i=400; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(20); }
    noTone(Pin_tone);
    delay(2000);
  
// звук "очередной шаг"
    for (int i=2500; i<6000; i=i*1.5) { tone(Pin_tone, i); delay(10); }
    noTone(Pin_tone);
    delay(2000);*/
  
// звук "ERROR"
    for (int j=0; j <3; j++){
    for (int i=1000; i<2000; i=i*1.1) { tone(Pin_tone, i); delay(10); }
    delay(50);
    for (int i=1000; i>500; i=i*1.9) { tone(Pin_tone, i); delay(10); }
    delay(50);
    }
    noTone(Pin_tone);
    delay(1000);
 //Звук Laser??
 for (int i = 25; i>1; i--) {
      for (int j = 20; j > 0; j--) {
        //analogWrite(ledPin, i*25);
        tone(Pin_tone, round((j*i)*(100/4)), 40);
        delay(40/10);
      }
      tone(Pin_tone, round((i)*(100/4)), 40);
    }
   noTone(Pin_tone);
   return;
}//if end
  else{switch (m)
      {
        case 1: {bm = ST_WARS; while((uint16_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm-=n;}
          break;
        case 2: {bm = NOK_TUNE; while((uint16_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm-=n;}
          break;
        /*case 3: {bm = PACMAN_1; while((uint16_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm=bx = PACMAN_1;}
          break;*/
        case 4: {bm = PACMAN_2; while((uint16_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm-=n;}
          break;
        case 5: {bm = C_GENA; while((uint16_t)pgm_read_word(&(bm->note))){n++;bm++;}//вычисляем количество нот в мелодии
                 bm-=n;}
          break;
      }
     }
 s= (float)(113.0/n);//вычисляем шаг в пикселях на шкале отрисовки сыгранных нот

  while(1)//Ожидание нажатия кнопок
  {if(k==0&&ts==0){
    ///Отрисовка графики плеера
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
        ////////
 /*myOLED.print("_Pos=", 5, 14);myOLED.printNumI(m, 60,14);
 myOLED.print(" n=",5,22);myOLED.printNumI(n,60,22);
 myOLED.print(" s=", 5, 30);myOLED.printNumF(s,3,60,30);
 myOLED.print("ts=", 5, 38);myOLED.printNumI(ts, 60,38);
 //myOLED.print("round(k*s)",2, 46);myOLED.printNumI(round(k*s),60,46);
myOLED.print("pgm=", 5, 46);myOLED.printNumI((uint16_t)pgm_read_word(&(bm->note)), 60,46);
myOLED.print("bm->note=", 2, 54);myOLED.printNumI(bm->note, 60,54);*/
 
        ////////
   myOLED.update();
 
///////////////////////////////////////// 
 

    if(ts && k<n)//если в режиме PLAY и сыграны не все ноты
 //while(bm->note)
     {
      k++;
      myOLED.drawRoundRect(9, 46, 9+round(k*s), 51);
      myOLED.printNumI(round(k*s*0.8849),70,30,3);
      myOLED.print("%", 96, 30);
      myOLED.update();
    tone(Pin_tone, (uint16_t)pgm_read_word(&(bm->note)), (uint16_t)pgm_read_word(&(bm->dur)));
    //digitalWrite(13, HIGH);
    //delay(bm->dur);
      //начало блока вызова цикла задержки аналог delay()
    { x=millis();
      while((millis()-x)<((uint16_t)pgm_read_word(&(bm->dur)))){if ( (button1.flagClick || button2.flagClick) == true )
        // был клик кнопки 1
        break;}
    }bm++;
    //digitalWrite(13, LOW);
    //delay(pauseBetweenNotes/2);
    }
  else {noTone(Pin_tone);
        if(k==n){k=0;bm-=n;ts=!ts;
                }
       }
    }//else end

}
