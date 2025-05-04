#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volitale uint8_t tot_overflow = 0;
uint8_t counter = 0;
const uint8_t segments[10] = {
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
ISR(TIMER0_OVF_vect) {
  tot_overflow++;
}
void timer0_init(void) {
  TCCR0A = (1 << FOC0A);
  TCCR0B &= ~((1 << CS00) | (1 << CS01));
  TCCR0B |= (1 << CS02);
  TCNT0 = 0;
  // enable overflow interrupt
  TIMSK0 |= (1 << TOIE0);
  // enable global interrupts
  sei();
  tot_overflow = 0;
}
void setup() {
  // put your setup code here, to run once:
  timer0_init();
  DDRC = 0b01111111;  //OUT
  PORTC = segments[counter];
}


void loop() {
  // put your main code here, to run repeatedly:
  if (tot_overflow >= 244) {
    if (TCNT0 >= 36) {
      TCNT0 = 0;
      tot_overflow = 0;
      counter++;
      counter %= 10;
    }
  }
  PORTC = segments[counter];
}
