#include "driver/uart.h"
HardwareSerial Serial2(2);

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,16,17);
}
void loop(){
  while (Serial2.available())Serial.println(char(Serial2.read()));
}
