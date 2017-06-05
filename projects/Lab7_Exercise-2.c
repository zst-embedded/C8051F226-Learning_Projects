/**
 * Lab 7 - Exercise 2
 * 
 * 2. Write a C program to make the single digit 7-segment display
 *    shows the number pressed from the keypad.
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
    0x67, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71, // F
    0x40  // -
};

void display(unsigned int d) {
    P1 = seven_segment[d];
}

unsigned int keyscan(unsigned int *key) {
    if (P34 == 1) { // key pressed.
        *key = P3 & 0x0f;
        return(1);
    } else {
        return(0);
    }
}

void main(void) {
    unsigned int key;
    setSystem();
    while (1) {
        if (keyscan(&key) != 0) {
            display(key); 
            // Display number/alphabet
        } else {
            display(16); 
            // Display dash
        }
    }
}