/**
 * Lab 4 - Exercise 1
 * 
 * 1. Write a program that first turn ON LED1, 3, 5, and 7, while LED2, 4, 6, and 8 are turned OFF.
 *    Subsequently, turn ON LED2, 4, 6, and 8 while 1, 3, 5, and 7 are turn OFF. This running
 *    sequence should be infinite.
 */

#include <f200.h>

void main(void) {
    unsigned int i;
    setSystem();
    P1 = 0x55;
    while (1) {
        P1 ^= 0xFF;
        for (i = 0; i < 50000; i++);
    }
}