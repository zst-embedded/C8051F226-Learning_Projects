/**
 * Lab 10 - Exercise 1 and 2
 * 
 * Write a C program to receive data from the PC through a serial port
 * and display it on the LCD panel.
 * 
 * 1. When a carriage return is received, the LCD screen will be cleared.  
 * 2. Automatically transmit a sentence "How are you?" when a string 
 *    of characters "hi" is received.
 */

#include <f200.h>
#include <string.h>

#define RS P35
#define RW P36
#define E P37

unsigned int j;

void setSystem();

/************/
// Provided
/************/
void strobe() {
    E = 1;
    for (j=0;j<150;j++);
    E=0;
    for (j=0;j<150;j++);
}

/************/
// Provided
/************/
void LCD_init() {
    unsigned int i;

    for(i<0;i<3;i++) {
        P2=0x30;
        RS=0;
        RW=0;
        strobe();
        for(j=0;j<150;j++);

        P2=0x38;
        strobe();

        P2=0x0c;
        strobe();

        P2=0x01;
        strobe();

        P2=0x02;
        strobe;
    }
}

/************/
// Provided
/************/
void LCD_print(unsigned int x) {
    P2=x;
    RS=1;
    RW=0;
    strobe();
}

/************/
// Provided
/************/
void LCD_cmd(unsigned int x) {
    P2=x;
    RS=0;
    RW=0;
    strobe();
}

/************/
// Provided
/************/
void baud_set() {
    TMOD=0x20;
    TH1=0xA0;
    SCON=0x50;
    TCON=0;
    TR1=1;
}

/******************/
// Exercise 1 and 2
/******************/
void LCD_println(char line[]) {
    char j = 0; // remember to init to zero
    while(line[j]) {
        LCD_print(line[j++]);
    }
}

void LCD_cursor(char x, y) {
    LCD_cmd(0x80 + (0x40 * y) + x);
}

void main(void) {
    char x, input[50], i = 0;
    setSystem();
    baud_set();
    LCD_init();

    RI = 0;
    E = 0;

    while(1) {
        while(RI==0); // wait until received char from serial
        RI = 0;

        x = SBUF;
        // Save character to string
        input[i++] = x;
        input[i] = '\0'; // Remember to add null-character

        switch (x) {
            case 0x08: // backspace cmd
            case 0x7F: // backspace cmd
                LCD_cmd(0x10); // cursor left cmd
                LCD_print(' '); // override with space
                LCD_cmd(0x10); // cursor left cmd
                i -= 2; // move index back to before character
                break;
            case '\r':
            case '\n':
                /* Exercise 1 */
                LCD_cmd(0x01); // clear screen
                i = 0;
                break;
            default:
                LCD_print(x);
                break;
        }

        /* Exercise 2 */
        if (strcmp(input, "hi") == 0 || strcmp(input, "hello") == 0) {
            LCD_println("How are you?");
            // LCD_cursor(0, 1);
        }
    }
}