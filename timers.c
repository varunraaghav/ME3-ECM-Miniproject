#include <xc.h>
#include "timers.h"

// comments from lab 3. no change to file here


void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b1000; // 1:256 //// multiply by 2^16 to get time taken to fill out 16 bit clock
    T0CON0bits.T016BIT=1;	//8bit mode	
    
    // it's a good idea to initialise the timer registers so we know we are at 0
    TMR0H=0b00001011;            //write High reg first, update happens when low reg is written to
    TMR0L=0b11011100;    // starting off at 3036 to get exactly 1 second
    T0CON0bits.T0EN=1;	//start the timer
}

