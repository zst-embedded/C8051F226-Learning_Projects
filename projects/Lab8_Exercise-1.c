/**
 * Lab 8 - Exercise 1
 * 
 * Stopwatch to display a counter 0 - 9999 with P02, P03, P04
 * being the start, stop and reset button respectively.
 */

#include <f200.h>
void setSystem();

void mux_display(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
	unsigned int i,j;
	for(j=0;j<1;j++){
		P2=0xE0|a;
		for (i=0;i<5000;i++);
		P2= 0xD0|b;
		for(i=0;i<5000;i++);
		P2=0xB0|c;
		for(i=0;i<5000;i++);
		P2=0x70|d;
		for(i=0;i<5000;i++);
	}
}

void display(unsigned int x) {
	unsigned int a,b,c,d;
	a=x/1000;
	b=(x % 1000)/100;
	c=(x % 100)/10;
	d=(x % 10);
	mux_display(a,b,c,d);
}


void main() {
	int x=0, y = 0;
	setSystem();

	TMOD=0x10; // Timer 1 set as 16-bit timer
	TR1=0; // timer is stopped
	TF1=0; // reset flag

	while(1) {
		for (y = 0; y < 20; y++) {
			TH1=0x4C;                                                                    
			TL1=0x26;
			while (TF1==0) {
				display(x);
				// Start Button
				if (P02 == 0) {
					TR1 = 1;
				}
				// Stop Button
				if (P03 == 0) {
					TR1 = 0;
				}
				// Reset Button
				if (P04 == 0) {
					x = -1;
					y = 21;
					break;
				}
			}
			TF1=0;
		}
		x++;
		if (x > 9999) {
			x = 0;
		}
	}
}