#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t interrupt_flag = 0;
ISR(ADC_vect) {
  interrupt_flag = 1;
}
void adc_init() {
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN) | (1 << ADIE);
  sei();
}
int16_t convert(uint8_t ch) {
  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8) | ch;
  ADCSRA |= (1 << ADSC);
  if (interrupt_flag != 1)
    return (-1);
  else {
    interrupt_flag = 0;
    return (ADC);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  adc_init();
}

void loop() {
  // put your main code here, to run repeatedly:
 int16_t  value = (convert(0)/1023.0)*5;
  if (value != -1)
    Serial.println(value);
}
