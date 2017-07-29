/**
 * Lab 11 - Exercise 2
 * 
 * Automatically transmit a 'B' when an 'A' is received using interrupts.
 */

#include <f200.h>
void setSystem();

// Serial Port Interrupt
void transmit (void) interrupt 4 {
	if (RI==1) {
		// P1 = 0xFF; // LEDs for debugging
		if (SBUF == 'A') {
			SBUF = 'B';
		}
		RI = 0;
	}

	if (TI == 1) {
		// P1 = 0x00; // LEDs for debugging
		TI = 0;
	}
}

void baud_set() {
	TMOD = 0x20;
	TH1 = 0xA0;
	SCON = 0x50;
	TCON = 0;
	TR1 = 1;
}

void main(void) {
	setSystem();
	baud_set();
	EA = 1;
	ES = 1;
	TI = 0;
	SBUF = '>';
	while (1);
}
