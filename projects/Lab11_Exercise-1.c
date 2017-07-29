/**
 * Lab 11 - Exercise 1
 * 
 * Blink LEDs when push button SW2 or SW3 is pressed using interrupts.
 */

#include <f200.h>
void setSystem();

// External Interrupt 0
// Blink LED 7
void sw2() interrupt 0 {
	unsigned int i, j;
	
	for (i = 0; i < 10; i++) {
		P1 ^= 1<<7;
		for (j=0;j<60000;j++);
	}
}

// External Interrupt 1
// Blink LED 6
void sw3() interrupt 2 {
	unsigned int i, j;
	
	for (i = 0; i < 10; i++) {
		P1 ^= 1<<6;
		for (j=0;j<60000;j++);
	}
}

void main(void) {
	unsigned int j;
	setSystem();

	EA = 1; // Enable Interrupts
	EX0 = 1; // Enable Ext Int 0
	EX1 = 1; // Enable Ext Int 1

	P1 = 0;

	// Blink LED 0
	while (1) {
		P1 ^= 1<<0;
		for (j=0;j<60000;j++);
	}
}



