#include<avr/io.h>
#include<util/delay.h>
void setup() {
  // put your setup code here, to run once:
  DDRB &= ~(1 << PB0);   //INPUT
  DDRC |= (1 << PC0);    //OUTPUT
  PORTB |= (1 << PB0);   // PULL UP
  PORTC |= (1 << PC0);  // OFF
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(PINB & (1 << PB0)))  //PRESSED
  {
    delay(30);
    if (!(PINB & (1 << PB0))) {
      while (!(PINB & (1 << PB0)))
        ;  //still pressed
        PORTC^=(1<<PC0);
    }
  }
}
