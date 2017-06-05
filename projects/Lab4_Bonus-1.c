/**
 * Lab 4 - Bonus 1
 * 
 * The LEDs will turned on in the following sequences and repeating:
 *     0000 0001
 *     0000 0011
 *     0000 0111
 *       (...)
 *     0011 1111
 *     0111 1111
 *     1111 1111
 */

#include <f200.h>

void delay() {
    unsigned int i;
    for (i = 0; i < 50000; i++);
}

void main(void) {
    int x;
    setSystem();
    while (1) {
        P1 = 0x00;

        // If I want 0b111, I take 1<<3 to get 0b1000.
        // then minus one to get 0b111
        for (x = 1; P1 < 0xFF; x <<= 1) {
            P1 = x - 1;
            delay();
        }

        // Alternatively: add the MSB to P1 on every loop
        /* 
        for (x = 1; x <= 0xFF; x <<= 1) {
            P1 = P1 + x;
            delay();
        }
        */
    }
}
