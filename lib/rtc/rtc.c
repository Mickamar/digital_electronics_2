#include "rtc.h"

uint8_t bcdToDec(uint8_t val) {
  return ( (val/16*10) + (val%16) ); //converts BCD to decimal
}

uint8_t decToBcd(uint8_t val) {
  return ( (val/10*16) + (val%10) );//converts decimal to BCD
}

void rtc_init() {
  
  TWBR = 72;  // Initializes I2C for communication with RTC
  TWSR = 0x00;
}

void rtc_start() {
  
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // starts the communication
  while (!(TWCR & (1 << TWINT)));
}

void rtc_stop() {
  
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); //stops the communication
}

void rtc_write(uint8_t data) { //Writes data to the i2c
  
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

uint8_t rtc_read() {// reads data from i2c
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
}

void rtc_write_seconds(uint8_t seconds) { //writes seconds from RTC to i2c
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x00); // address of seconds register
  rtc_write(decToBcd(seconds)); 
  rtc_stop();
}

void rtc_write_minutes(uint8_t minutes) { //writes minutes from RTC to i2c
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x01); // address of minutes register
  rtc_write(decToBcd(minutes)); 
  rtc_stop();
}

void rtc_write_hours(uint8_t hours) { //writes hours from RTC to i2c
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x02); // address of hours register
  rtc_write(decToBcd(hours)); 
  rtc_stop();
}
void rtc_read_seconds(uint8_t *seconds) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x00); 
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *seconds = bcdToDec(rtc_read() & 0x7F); 
  rtc_stop();
}

void rtc_read_minutes(uint8_t *minutes) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x01); 
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *minutes = bcdToDec(rtc_read());
  rtc_stop();
}

void rtc_read_hours(uint8_t *hours) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x02); 
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *hours = bcdToDec(rtc_read() & 0x3F); 
}