#include<avr/io.h>
#include<avr/interrupt.h>
#include<Arduino.h>
uint8_t i = 1;
void spi_init_master(void){
  DDRB |= (1<<DD3) | (1<<DD2) | (1<<DD5);
  DDRB &= ~(1<<DD4);
  PORTB |= (1<<DD2);
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}
void spi_write(uint8_t data){
  SPDR = data;
  while(!(SPSR & (1<<SPIF)));
  volatile char flush_buffer = SPDR;
  flush_buffer += 1;
}
uint8_t spi_read(void){
  SPDR = 0xFF;
  while(!(SPSR & (1<<SPIF)));
  uint8_t flush_buffer = SPDR;
  return flush_buffer;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  spi_init_master();
  PORTB &= ~(1<<DD2);//select slave
  _delay_ms(300);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (i>15){
    i=1;
  }
  spi_write(i++);
  Serial.print(i);
  Serial.print(" is sent from master, ");
  _delay_ms(10);
  uint8_t t = spi_read();
  Serial.print(t);
  Serial.print(" is recieved from slave \n");
  _delay_ms(300);
}
