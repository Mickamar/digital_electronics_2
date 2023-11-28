#include "rtc.h"

uint8_t bcdToDec(uint8_t val) {
  return ( (val/16*10) + (val%16) );
}

uint8_t decToBcd(uint8_t val) {
  return ( (val/10*16) + (val%10) );
}

void rtc_init() {
  // Nastavení I2C sběrnice
  TWBR = 72;  // Rychlost 100 kHz při 16 MHz krystalu
  TWSR = 0x00;
}

void rtc_start() {
  // Spuštění I2C komunikace
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

void rtc_stop() {
  // Ukončení I2C komunikace
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void rtc_write(uint8_t data) {
  // Zápis dat na I2C sběrnici
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

uint8_t rtc_read() {
  // Čtení dat z I2C sběrnice
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
}

void rtc_read_seconds(uint8_t *seconds) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x00); // Adresa registru sekund
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *seconds = bcdToDec(rtc_read() & 0x7F); // Zakrytí bitu CH
  rtc_stop();
}

void rtc_read_minutes(uint8_t *minutes) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x01); // Adresa registru minut
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *minutes = bcdToDec(rtc_read());
  rtc_stop();
}

void rtc_read_hours(uint8_t *hours) {
  rtc_start();
  rtc_write(RTC << 1);
  rtc_write(0x02); // Adresa registru hodin
  rtc_start();
  rtc_write((RTC << 1) | 1);
  *hours = bcdToDec(rtc_read() & 0x3F); // Zakrytí bitu 24-hodin/AM/PM
  rtc_stop();
}