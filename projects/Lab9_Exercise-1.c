/**
 * Lab 9 - Exercise 1
 * 
 * Send "Hello World" over UART to PC with different baud rates.
 */

#include <f200.h>
void setSystem();

/* Calculate baud rate on-the-fly */
char TH1_from_baud(long crystal, int baud) {
	return 0x100 - (crystal / 12.0) / (baud * 32.0);
}

void baud_set() {
	TMOD = 0x20; // Timer 1 as 8-bit auto reload

	/* Set baud rate */ 
	// TH1 = 0xA0; // Baud rate of 300bps for 11.05MHz crystal
	// TH1 = 0xE8; // Baud rate of 1200bps for 11.05MHz crystal
	// TH1 = 0xF4; // Baud rate of 2400bps for 11.05MHz crystal
	// TH1 = 0xFD; // Baud rate of 9600bps for 11.05MHz crystal
	TH1 = TH1_from_baud(11.059e6, 2400); // Calculate baud rate

	SCON = 0x50; // 8-bit UART, Enable Serial
	TCON = 0;
	TR1 = 1; // Start Timer 1
}

void main(void) {
	char * text = "Hello World!\n\r";
	setSystem();
	baud_set();
	while (*text) {
		TI=0; // Clear Transmit Interrupt
		SBUF = *text;
		text++;
		while(TI==0); // wait until finish transmitting
	}
}

/*
// Alternatively:
void main(void) {
	unsigned int i;
	char text[] = "Hello World!\n\r";
	setSystem();

	baud_set();
	while(text[i]) {
		TI=0; // Clear Transmit Interrupt
		SBUF = text[i++];
		while(TI==0); // wait until finish transmitting
	}
}
*/


