#include<avr/io.h>
#include<util/delay.h>
uint8_t count=0;
// a pin 0 b -->1 c-->2 d-->3 e--> 4 f-->5 g-->6
#define count0 0b00111111 // a b c d e f 
#define count1 0b00000110 //b c
#define count2 0b01011011 //a b d e g 
#define count3 0b01001111 //a b c d g 
#define count4 0b01100110 // b c f g 
#define count5 0b01101101 // a f g c d
#define count6 0b01111101 //  c d e g f
#define count7 0b00000111 //a b c 
#define count8 0b01111111// a b c d e f g 
#define count9 0b01101111 // a b c d f g
void disply(uint8_t count){
  if(count==0) PORTD=count0;
  else if(count==1) PORTD=count1;
  else if (count==2) PORTD=count2;
  else if (count==3) PORTD=count3;
  else if (count==4) PORTD=count4;
  else if (count==5) PORTD=count5;
  else if (count==6) PORTD=count6;
  else if (count==7) PORTD=count7;
  else if (count==8) PORTD=count8;
  else  PORTD=count9;
}
void setup() {
  // put your setup code here, to run once:
  DDRC&=~(1<<PC4);
  DDRD=0b01111111;
  PORTD=0x00;//0ff
  disply(count);

}

void loop() {
  // put your main code here, to run repeatedly:
  if((PINC&(1<<PC4))){

    count++;
    count %=10;
  } 
  disply(count);
}
