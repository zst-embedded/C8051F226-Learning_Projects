/**
 * Lab 1 - Introduction
 * 
 * Pressing switches SW2 through SW5 will cause 
 * the LED on P01 to blink at different speeds.
 */

#include <f200.h>

void delay(unsigned int x) {
    while (x-- != 0);
}

void main() {
    int wait = 20000;
    setSystem();
    P1 = 0x00;

    while (1) {
        if (P02 == 0) wait = 10000;
        if (P03 == 0) wait = 20000;
        if (P04 == 0) wait = 40000;
        if (P05 == 0) wait = 60000;

        P1 = 0x00;
        delay(wait);
        P1 = 0x01;
        delay(wait);

    }
}