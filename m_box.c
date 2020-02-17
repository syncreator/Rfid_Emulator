#include <avr/pgmspace.h>
#include <Arduino.h>

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
};

void Music(byte n, byte Pin_tone))//номер мелодии или указатель на мелодию?
{ MUSIC *bm ;
  switch (n)
      {
        case 0: bm = ST_WARS;
          break;
        case 1: bm = NOK_TUNE;
          break;
        case 2: bm = PACMAN_1;
          break;
        case 3: bm = PACMAN_2;
          break;
        case 4: bm = C_GENA;
          break;
        case 5: bm = C_GENA;
          break;
      }
  /// звуки для оформления
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
    
  
    //Основной цикл воспроизведения
     for (int thisNote = 0; thisNote < sizeof(Array)/sizeof(Array[0]); thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(Pin_tone, melody[thisNote], noteDuration);
    //digitalWrite(13, HIGH);
    delay(noteDuration);
    //digitalWrite(13, LOW);
    //delay(pauseBetweenNotes/2);
  }
  noTone(Pin_tone);


}
