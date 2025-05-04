#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void adc_init(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}
uint16_t adc_read(uint8_t ch) {
  ch&=0b00000111;
  ADMUX=(ADMUX & 0xF8)|ch;
  ADCSRA|=(1<<ADSC);
  while(ADCSRA&(1<<ADSC));
  return (ADC);
}
void setup() {
  // put your setup code here, to run once:
  adc_init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t result=adc_read(0);
  Serial.println(result);
}
