/**
 * Lab 11 - Bonus 1
 * 
 * Since the 8051 does not have a way to generate PWM in hardware,
 * it can be simulated in software using interrupts and timers.
 *
 * Timer 0 interrupt is used for PWM generation. Upon every 
 * interrupt routine , port 1 LEDs are toggled and the new reload
 * value for Timer 0 is set to produce the correct duty cycle.
 * 
 * The PWM signal has a frequency of 256 timer clock cycles (hardcoded).
 * The board has a 11.059MHz crystal
 *   Calculation for PWM frequency
 *   = 256 * 1/(11.059MHz / 12)
 *   = 277.78 us OR 3.60 kHz
 *
 * Timer 1 interrupt is used to change the duty cycle after some
 * time. The interrupt routine code increments the value to produce
 * a PWM signal with reference to a triangle waveform.
 */

#include <f200.h>

void setSystem();

unsigned int highVal = 250;
unsigned int lowVal = 5;
float duty_cycle_percent = 0.0;

float abs(float c) {
    return (c < 0) ? (-c) : c;
}

/**
 * The timer is set to 16-bit mode, but only 8-bits are used.
 * This is because we do not want auto-reload that is together
 * with the 8-bit mode.
 */
void setTimer0Value(unsigned int val) {
    TH0 = 0xFF;
    TL0 = val;
}

/**
 * Timer 0 Interrupt
 *   Duty cycle percentage increments from -1 to +1 in steps of 0.025
 *   The absolute value of the percentage is taken. Hence creating a 
 *   triangle wave.
 *   The low and high values for Timer 0 are calculated based on the
 *   new duty cycle.
 */
void pwm(void) interrupt 1 {
    TR0 = 0; // Stop Timer 0
    setTimer0Value( (P1 == 0) ? highVal : lowVal ); // Set next reload value
    P1 ^= 0xFF; // Toggle P1 LEDs to produce PWM    
    TR0 = 1; // Start Timer 0
}

/**
 * Timer 1 Interrupt
 *   Duty cycle percentage increments from -1 to +1 in steps of 0.025
 *   The absolute value of the percentage is taken. Hence creating a 
 *   triangle wave.
 *   The low and high values for Timer 0 are calculated based on the
 *   new duty cycle.
 */
void changeDuty(void) interrupt 3 {
    duty_cycle_percent += .025;
    if (duty_cycle_percent > 1.0) {
        duty_cycle_percent = -1.0;
    }

    lowVal = abs(duty_cycle_percent) * 255;
    highVal = 255 - lowVal;
}

void main(void) {
    setSystem();

    P1 = 0; // Turn off all LEDs

    TMOD = 0x11; // Timer 0 as 16 bit, Timer 1 as 16 bit

    TR0 = 1; // Enable timer 0
    TF0 = 0; // Reset timer 0 flag
    setTimer0Value(0);

    /* Calculation for Timer 1:
     * Time per increment
     *   (65536) * (11.059MHz / 12)^-1
     *   = 71.1123971 ms
     * 
     * Timer per cycle  
     *   Since 0.025 steps are used
     *   71.1123971 ms * ((1--1) / .025)
     *   = 5.7s
     */
    TR1 = 1; // Enable timer 1
    TF1 = 0; // Reset timer 1 flag
    // No reload value

    EA = 1; // Enable interrupts
    ET0 = 1; // Timer 0 interrupt
    ET1 = 1; // Timer 1 interrupt

    while (1);
}
