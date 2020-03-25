#include <SoftwareSerial.h>
SoftwareSerial RfidReader(0, 1);
int num;
int count = 0;
void setup(){
Serial.begin(9600); 
RfidReader.begin(9600);
}
void loop() 
{
 if (RfidReader.available() > 0)
  {count++;
num = RfidReader.read();
Serial.print(num, DEC);
    if(count >= 14)
    {Serial.println(' ');
     count = 0;}
  else {
Serial.print(", ");
  }
 }
}
/////// Строчный вариант
#include <SoftwareSerial.h>
 
SoftwareSerial rdm6300(7, 8);
String s = "";
 
void setup() {
  rdm6300.begin(9600);
  Serial.begin(9600);
}
 
void loop() {
  if (rdm6300.available() > 0) {
    while (rdm6300.available() > 0) {
      char c = rdm6300.read();
      s += c;
      delay(3);
    }
 
    Serial.println(s);
    s = "";
  }
}
/////// Еще вариант
