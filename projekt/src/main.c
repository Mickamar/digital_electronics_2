#include <stdio.h>
#include "gpio.h"
#include "rtc.h"

#define SENZOR_PIN 1 // A1
#define LAMP 3 // D3

int main() {
    uint8_t hours, minutes, seconds;
    printf("---- Test fotorezistoru ----\n");
    GPIO_mode_output(&DDRB, LAMP);
    rtc_init();
    while (1) {
        int war = GPIO_read(&PINB, SENZOR_PIN);
        printf("%d\n", war);

        rtc_read_hours(&hours);
        rtc_read_minutes(&minutes);
        rtc_read_seconds(&seconds);
        printf("Aktuální čas: %02d:%02d:%02d\n", hours, minutes, seconds);

        if (war > 700) {
            printf("LED svítí\n");
            //GPIO_write_high(&PORTB, LAMP);
        //} else {
           // GPIO_write_low(&PORTB, LAMP);
        }
        
        _delay_ms(1000);
    }

    return 0;
}



// odpor 1k první noha GND druhá noha A1
//Fotorezistor	První noha	A1 Druhá noha	5 V