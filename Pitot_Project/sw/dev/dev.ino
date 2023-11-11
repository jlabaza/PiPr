

#include <ShiftRegister74HC595.h>

//Generate shift register object,<number of registers> (data pin, clockpin,latchpin)
ShiftRegister74HC595<1> sr(11,10,9);
const int clr = 8;

void setup() {
//set pins to output because they are addressed in the main loop
  Serial.begin(9600);
  Serial.println("START");
}

int num2bin(int num){
  int out = 0;
  switch(num){
    case 0:
      out = B10011111;
      break;
    case 1:
      out = B00000110;
      break;
    case 2:
      out = B01011011;
      break;     
  }
  return out;
}

void loop() {
//  sr.setAllHigh();
//  delay(3000);
//  int bin = num2bin(0);  
//  Serial.println(bin);
  digitalWrite(clr,LOW);
  Serial.println("clear");
  delay(100);
  digitalWrite(clr,HIGH);
  delay(100);
  sr.setAll(B1101111);
  delay(1000);
  Serial.println("Starting Get");
  for(int i=0;i<=7;i++){
    Serial.println(sr.get(i));
    delay(300);
  }
  delay(1500);
  Serial.println("OTHER");
  digitalWrite(clr,LOW);
  Serial.println("clear");
  delay(100);
  digitalWrite(clr,HIGH);
  delay(100);
  sr.setAll(B1110000);
  delay(1000);
  Serial.println("Starting Get");
  for(int i=0;i<=7;i++){
    Serial.println(sr.get(i));
    delay(300);
  }
  sr.setAllHigh();
  delay(3000);


}
