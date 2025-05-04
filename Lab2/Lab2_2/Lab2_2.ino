#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
ISR(INT1_vect) {
  uint8_t count=5;
  while(count){
    PORTC|=(1<<PC0)|(1<<PC1)|(1<<PC2);
    _delay_ms(500);
    PORTC&=~((1<<PC0)|(1<<PC1)|(1<<PC2));
    _delay_ms(500);
    count--;
  }
}
void INT1_init(void) {
  SREG &= ~(1 << 7);
  DDRD &= ~(1 << PC3);  //INT_1
  PORTD |= (1 << PC3);  //PULL UP
  EIMSK |= (1 << INT1);
  EICRA |= (1 << ISC11);
  EICRA &= ~(1 << ISC10);  //FALLING EDGE
  SREG |= (1 << 7);
}
void setup() {
  // put your setup code here, to run once:
  INT1_init();
  DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
  PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTC = 0x01;
  _delay_ms(500);
  PORTC = 0x02;
  _delay_ms(500);
  PORTC = 0x04;
  _delay_ms(500);
}
