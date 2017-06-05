#include <f200.h>

//----- Delay2 Subroutine ------- 
void delay2(unsigned int duration)
{
	while ((duration--)!=0);
}

void setSystem()
/*-----------------------------------------------------------------------
	Diasable watchdog and switch off internal to external oscillator.
	Configure system input/output ports
-------------------------------------------------------------------------*/
{

	WDTCN = 0xde;			// Disable Watchdog
  	WDTCN = 0xad;

 	OSCXCN = 0x67;
	delay2 (60000);			// Wait for oscillation to stable.
	
	while((OSCXCN & 0x80)==0);	// Wait for external Osc to stable.
	OSCICN|= 0x08;
	
	PRT0CF |= 0x40;		// Configure speaker output port P0.6 as push-pull
  	PRT2CF |= 0xFF;		// Configure port as push-pull
 	PRT1CF |= 0xFF;		// Configure port a as push-pull
	PRT3CF |= 0xe0;		// Configure P35 to P37 as push-pull

	PRT0MX |= 0x0d;		// Enable Serial IO Port & Interrupts

	P0 |= 0x3c;		// Set P0.2 to P0.5 as input.
	P3 |= 0x1f; 		// Set P30 to P34 as input.	
  	P2 = 0;
}
