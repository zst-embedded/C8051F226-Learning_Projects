/**
 * Lab 5 - All exercises
 * 
 * 1. Write a program to make the single digit 7-segment display to
 *    count from 9 to 0.
 *
 * 2. Write a program to make the single digit 7-segment display to
 *    count from 0 to 9 and 9 to 0 repeatedly.
 *
 * 3. Write a program to make the single digit 7-segment display to
 *    count on even number followed by odd number.
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
    for (i = 0; i < 65000; i++);
}
void main(void) {
    int x;
    setSystem();

    // Ex1 and Ex2
    while (1) {
        // Count 0 -> 9
        for (x = 0; x < 10; x++) {
            display(x);
            delay();
        }
        // Count 9 -> 0 
        for (x = 9; x >= 0; x--) {
            display(x);
            delay();
        }
    }

    /*
    // Ex3
    while (1) {
        // Count up even numbers
        for (x = 0; x < 10; x += 2) {
            display(x);
            delay();
        }
        // Count up odd numbers
        for (x = 1; x < 10; x += 2) {
            display(x);
            delay();
        }
    }
    */
}
