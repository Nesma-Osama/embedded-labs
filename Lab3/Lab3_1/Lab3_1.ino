#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile uint8_t tot_overflow;
ISR(TIMER_OVF_vect) {
  tot_overflow++;
}
void timer2_init(void) {
  TCCR2B |= (1 << CS21) | (1 << CS20);
  TCNT2 = 0;
  TIMSK2 |= (1 << TOIE2);
  TCCR2A = (1 << FOC2A);
  sei();
  tot_overflow = 0;
}
void setup() {
  // put your setup code here, to run once:
  DDRC |= (1 << PC0);
  PORTC &= ~(1 << PC0);
  timer2_init();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (tot_overflow >= 30) {
    if (TCNT2 >= 131) {
      PORTC ^= (1 << PC0);
      tot_overflow = 0;
      TCNT2 = 0;
    }
  }
}
