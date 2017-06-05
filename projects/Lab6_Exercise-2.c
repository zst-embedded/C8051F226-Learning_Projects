/**
 * Lab 6 - Exercise 2
 * 
 * 2. Write a program to make the four digit 7-segment display
 *    to count from 00, 01, 02, 03 to 99 and from 99, 98, 97, 96 to 0 repeatedly
 */

void delay() {
    unsigned int i;
    for (i = 0; i < 1000; i++);
}

void multiplex(int number) {
    int digit[4], mux;
    digit[0] = number % 10;
    number /= 10;
    digit[1] = number % 10;
    number /= 10;
    digit[2] = number % 10;
    number /= 10;
    digit[3] = number % 10;
    for (mux = 0; mux < 4; mux++) {
         P2 = ~(1<<mux) << 4 | digit[3-mux];
         delay();
    }
}

void main(void) {
     setSystem();
     while (1) {
        int x;
        for (x = 0; x <= 99; x++) {
            // Show 50 frames of the multiplexing
            // to slow down the count up on the display
            int i;
            for (i = 0; i < 50; i++) 
                multiplex(x + x * 100);
        }
     }
}