#include <SPI.h>

const float shiftDelay = 0.04167 ; 
//Define from clock freq. particular to shift reg: (74565 =  or 6B565 = )
const int dataPin = 13; //connects to SERIAL IN - data
const int clockPin = 12; //connects to SERIAL REGISTER CLOCK - clock
const int latchPin = 14; //connects to REGISTER CLOCK - latch

// Uncomment if wanted
//const int SRCLR = ; //connects to SERIAL CLEAR
//const int OE = ; //connects to OUTPUT ENABLE (G)
void setup() 
{
 Serial.begin(9600);
 pinMode(dataPin,OUTPUT);
 pinMode(clockPin,OUTPUT);
 pinMode(latchPin,OUTPUT);
 pinMode(2,OUTPUT);

}

void dispNum(float num); //takes in number to display
void pulseClock();
void pulseLatch();

void loop()
{
  for(float i=0;i<100;i+=0.1)
  {
    dispNum(i);
    delay(25);
  }
}


void dispNum(float num)
{

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
  
  int number = static_cast<int>(num*10);
  int num1 = number%10;
  int num10 = (number%100)/10;
  int num100 = number/100;
  
  int seg100 = sevSeg[num100];
    if(num100==0)
  {
    seg100 = 0b00000000;
  }
  int seg10 = (0b10000000 + sevSeg[num10]);
  int seg1 = sevSeg[num1];


  int segs[3] = {seg1, seg10, seg100};
  for (int i = 0; i<3; i++)
  {
    int digit = segs[i];
    for (int j = 7; j>=0; j--)//8 bits to write
    {
      digitalWrite(dataPin,!((digit >> j) & 1)); 
      //bitShift from R->L, common cathode HIGH is dark
      pulseClock(); //Cycle clock 1 bit
    }
  }
  pulseLatch();
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
