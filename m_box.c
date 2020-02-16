#include <avr/pgmspace.h>
#include <Arduino.h>

//Структура мелодии
struct MUSIC{
  int note
  uint8_t dur;
};

void Music(byte n, byte Pin_tone))//номер мелодии или указатель на мелодию?
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
    
    //Основной цикл воспроизведения
     for (int thisNote = 0; thisNote < amountNotes; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(Pin_tone, melody[thisNote], noteDuration);
    //digitalWrite(13, HIGH);
    delay(noteDuration);
    //digitalWrite(13, LOW);
    //delay(pauseBetweenNotes/2);
  }
  noTone(Pin_tone);


}
