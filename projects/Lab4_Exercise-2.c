/**
 * Lab 4 - Exercise 2
 * 
 * 2. Write a program that creates a running LED on the LED bar that
 *    runs from left to right and right to left repeatedly.
 */

#include <f200.h>

void delay() {
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void main(void) {
    setSystem();
    P1 = 0x01;
    while (1) {
        while ((P1 & 0x80) == 0) {
            P1 <<= 1;
            delay();
        }
        while ((P1 & 0x01) == 0) {
            P1 >>= 1;
            delay();
        }
    }
}