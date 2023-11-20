#include <SPI.h>

const char shiftDelay = 0.04167 ; 
//Define from clock freq. particular to shift reg: (74565 =  or 6B565 = )
const int dataPin = 11; //connects to SERIAL IN - data
const int clockPin = 10; //connects to SERIAL REGISTER CLOCK - clock
const int latchPin = 9; //connects to REGISTER CLOCK - latch

// Uncomment if wanted
//const int SRCLR = ; //connects to SERIAL CLEAR
//const int OE = ; //connects to OUTPUT ENABLE (G)
void setup() 
{
 Serial.begin(9600);
 pinMode(dataPin,OUTPUT);
 pinMode(clockPin,OUTPUT);
 pinMode(latchPin,OUTPUT);

}

void dispNum(int num); //takes in number to display
void pulseClock();
void pulseLatch();

void loop()
{
//  char receiveNum;
//  if (Serial.available() >0)
//  {
//    char receiveNum = Serial.read();
//  }
//  int curNum = receiveNum - '0';
  for(int i=0;i<100;i++)
  {
    dispNum(i);
    delay(3000);
  }
}


void dispNum(int num)
{
  num*=10;
  int sevSeg[10] ={
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
  };

  int seg = sevSeg[num];
  
  for(int i = 7; i>=0; i--)//8 bits to write
  {
    digitalWrite(dataPin,!((seg >> i) & 1)); 
    //bitShift from R->L, common cathode HIGH is dark
    pulseClock(); //Cycle clock 1 bit
  }
  pulseLatch(); //Latch data
  

}

void pulseClock()
{
  digitalWrite(clockPin,HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(clockPin,LOW);
  delayMicroseconds(shiftDelay);
}
void pulseLatch()
{
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(latchPin,LOW);
  delayMicroseconds(shiftDelay);
}
