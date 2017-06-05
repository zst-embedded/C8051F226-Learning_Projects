/**
 * Lab 7 - Exercise 1
 * 
 * 1. Write a C program to make the single digit 7-segment display start counting from 0 to 9
 *    repeatedly when SW2 is pressed and released. The counting should stop when SW3 is pressed.
 */

#include <f200.h>

const unsigned int seven_segment[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x67  // 9
};

void display(unsigned int d) {
    P1 = seven_segment[d];
}

void delay() {
    unsigned int i;
    for (i=0;i<50000;i++);
}


void main(void) {
    int counting = 0, number = 0;
    unsigned int delay = 0;
    setSystem();

    P02 = 1; // initialize P0.2 as input
    P03 = 1; // initialize P0.3 as input
    P1 = 0x00; // turn off all the LEDs

    while (1) {
        display(number);
        
        // Start counting on SW2
        if(!P02) { 
            counting = 1;
        }
        // Stop counting on SW3
        if(!P03) {
            counting = 0;
        }

        if (counting) {
            if (delay++ >= 20000) {
                delay = 0;
                number++;
                if (number >= 9)
                    number = 0;
            }
        }
    }
}
