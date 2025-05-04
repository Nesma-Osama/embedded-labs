#include<avr/io.h>
#include<avr/interrupt.h>
#include<Arduino.h>
#define SS PB2
#define SCLK PB5
#define MOSI PB3
#define MISO PB4
uint8_t data_rec = 0;
void spi_init_slave(void){
  DDRB |= (1<<MISO);
  DDRB &= ~(1<<MOSI) | (1<<SCK) | (1<<SS);
  SPCR = (1<<SPE);
}
void spi_write(uint8_t data){
  volatile char flush_buffer;
  SPDR = data;
  while(!(SPSR & (1<<SPIF)));
  flush_buffer = SPDR;
}
uint8_t spi_read(void){
  SPDR = 0xFF;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  spi_init_slave();
  PORTB &= ~(1<<DD2);//select slave
  _delay_ms(300);
}

void loop() {
  // put your main code here, to run repeatedly:
  data_rec = spi_read();
  Serial.print(data_rec);
  Serial.print(" is recieved from master, ");
  data_rec += 10;
  spi_write(data_rec);
  Serial.print(data_rec);
  Serial.print(" is sent to master \n");
}
