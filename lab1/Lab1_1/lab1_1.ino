#include<avr/io.h>
#include<util/delay.h>
void setup() {
  // put your setup code here, to run once:
  DDRD|=(1<<PD6);
  PORTD|=(1<<PD6);//OFF
}

void loop() {
  // put your main code here, to run repeatedly:
   PORTD&=~(1<<PD6);//ON
   delay(1000);//1 s
   PORTD|=(1<<PD6);//OFF
     delay(1000);//1 s
}
