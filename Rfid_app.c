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

