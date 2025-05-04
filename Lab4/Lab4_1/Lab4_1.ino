#include<avr/io.h>
#include<avr/interrupt.h>
void adc_init(){
  ADMUX=(1<<REFS0);
  ADCSRA=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADEN);
}
uint16_t convert(uint8_t ch){
  ch&=0b00000111;
  ADMUX = (ADMUX & 0xF8)|ch;
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return (ADC);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  adc_init();
}

void loop() {
  // put your main code here, to run repeatedly:
 uint16_t  value=convert(0);
   Serial.println(value);
}
