/**
 * Lab 7 - Bonus 1
 * 
 * The number of LEDs lighted up is controlled by the number
 * pressed on the keypad. (For 0 through 8 only)
 */

#include <f200.h>


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
    P1 = 0; // Turn off all LEDs on P1
    while (1) {
        if(keyscan(&key) != 0) {
            // We only have 8 LEDs, ignore those numbers above 8
            if (key <= 8) {
                P1 = (1<<key) - 1;
                // If I want 0b111, I take 1<<3 to get 0b1000.
                // then minus one to get 0b111
            }
        }
    }
}