#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
ISR(INT0_vect){
  PORTC^=(1<<PC0);
}
void INT0_init(void){
  SREG&=~(1<<7);
  DDRD&=~(1<<PD2);
  EIMSK|=1<<INT0;
  EICRA|=(1<<ISC00)|(1<<ISC01);
  SREG|=(1<<7);
}
void setup() {
  // put your setup code here, to run once:
  INT0_init();
  DDRC|=1<<PC0;  
  PORTC&=~(1<<PC0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
