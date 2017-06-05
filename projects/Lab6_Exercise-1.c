/**
 * Lab 6 - Exercise 1
 * 
 * 1. Write a program to make the four digit 7-segment display
 *    to count from 00, 11, 22, 33 to 99 repeatedly
 */

#include <f200.h>

void delay() {
    unsigned int i;
    for (i = 0; i < 50000; i++);
}

void main(void) {
    setSystem();
    while (1) {
        int x;
        for (x = 0; x < 10; x++) {
            // Display number on middle two digits
            // 0b1001 (active-LOW common pin)
            P2 = 0x90 | x;
            delay();
        }
    }
}