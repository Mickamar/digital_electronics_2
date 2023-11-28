#ifndef RTC_H
#define RTC_H

#include <avr/io.h>
#include <util/delay.h>

#define RTC 0x68

uint8_t bcdToDec(uint8_t val);
uint8_t decToBcd(uint8_t val);

void rtc_init();
void rtc_start();
void rtc_stop();
void rtc_write(uint8_t data);
uint8_t rtc_read();
void rtc_read_seconds(uint8_t *seconds);
void rtc_read_minutes(uint8_t *minutes);
void rtc_read_hours(uint8_t *hours);

#endif

