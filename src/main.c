#include <stdio.h>
#include "gpio.h"
#include "rtc.h"
#include "uart.h"
#include "oled.h"
#include "twi.h"
#include <stdlib.h> 
#include "timer.h"
#include <avr/io.h>         
#include <avr/interrupt.h>




#define SENZOR_PIN PC1 // A1
#define LAMP PD3 // D3


int main() {
    
    char time_string[9];
    char buffer[10];
    uint8_t hours, minutes, seconds;

    

    uart_init(UART_BAUD_SELECT(9600, F_CPU));
    TIM1_OVF_1SEC
    TIM1_OVF_ENABLE
    sei();
    
    GPIO_mode_input(&DDRC, SENZOR_PIN);
    GPIO_mode_output(&DDRB, LAMP);

    rtc_init();
    rtc_write_seconds(0); 
    rtc_write_minutes(10); 
    rtc_write_hours(13);

    while (1) {
        int war = GPIO_read(&PINC, SENZOR_PIN);
        itoa(war, buffer, 10);
        
        
        uart_puts(buffer);
        uart_puts("\n");
        rtc_read_hours(&hours);
        rtc_read_minutes(&minutes);
        //rtc_read_seconds(&seconds);


        itoa(hours,time_string,10);
        uart_puts(time_string);
        uart_puts(":");
        itoa(minutes,time_string,10);
        uart_puts(time_string);
        uart_puts(":");
        //itoa(seconds,time_string,10);
        //uart_puts(time_string);
        //uart_puts("\n");
        
        
        if ((hours >= 18 && hours <= 23) || (hours >= 0 && hours < 7) || war == 0) {
            uart_puts("Zapínání lampy mezi 18:00 a 7:00 nebo při war == 0\n");
            GPIO_write_high(&PORTB, LAMP); // Zapnutí lampy
        } else {
            uart_puts("LED nesvítí\n");
            GPIO_write_low(&PORTB, LAMP); // Vypnutí lampy
    }

        //if (war == 0) { //no light, diod shine
          //  uart_puts("LED svítí\n");
            //GPIO_write_high(&PORTB, LAMP);
        //} else {
          //  uart_puts("LED nesvítí\n");
            //GPIO_write_low(&PORTB, LAMP);
        //}
        
        //_delay_ms(1000);
    //}
        // Kontrola času pro zapnutí lampy od 18:00:00 do 06:59:59
      //  if ((hours >= 18 && hours <= 23) || (hours >= 0 && hours < 7)) {
       //     uart_puts("Zapínání lampy mezi 18:00 a 7:00\n");
        //    GPIO_write_high(&PORTB, LAMP); // Zapnutí lampy
        //} else {
          //  uart_puts("LED nesvítí\n");
            //GPIO_write_low(&PORTB, LAMP); // Vypnutí lampy
     //}

    return 0;
}


// odpor 1k první noha GND druhá noha A1
//Fotorezistor	První noha	A1 Druhá noha	5 V
//pin D3 > dioda > odpor> GND
