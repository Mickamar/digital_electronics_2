#include <stdio.h>
#include "gpio.h"

#define SENZOR_PIN 1 // A1
#define LAMP 3 // D3

int main() {
    printf("---- Test fotorezistoru ----\n");
    GPIO_mode_output(&DDRB, LAMP);

    while (1) {
        int war = GPIO_read(&PINB, SENZOR_PIN);
        printf("%d\n", war);
        
        if (war > 700) {
            printf("LED svítí\n");
            GPIO_write_high(&PORTB, LAMP);
        } else {
            GPIO_write_low(&PORTB, LAMP);
        }
        
        delay(200);
    }

    return 0;
}



// odpor 1k první noha GND druhá noha A1
//Fotorezistor	První noha	A1 Druhá noha	5 V