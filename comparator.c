#include <xc.h>
#include "comparator.h"


// comments from lab 3. file not changed

void DAC_init(void)
{
    DAC1CON0bits.PSS=0b00;      //3.3V for positive source (Vdd)
    DAC1CON0bits.NSS=0b0;      //0v for Negative source (Vss))
	//5-bit DAC value to set output voltage
    // min is 0 = 0V
    // max is 2^5-1 = 31 = 3.3V
    DAC1CON1bits.DAC1R=0b01010; // adjust according to ambient light 27~2.87V
    DAC1CON0bits.DAC1EN=1;      //turn on DAC
}


void Comp1_init(void)
{
    TRISFbits.TRISF7=1;		// set pin RF7 as input
    
    // ____________________ INITIALISING RISING EDGE COMPARATOR: CM1
    
    CM1NCHbits.NCH=0b011; 	// pin RF7 as input for comparator
    CM1PCHbits.PCH=0b101;   //use DAC output for positive input
    CM1CON0bits.HYS=1;      //a little bit of hysteresis to stop multiple triggers
    CM1CON0bits.POL=1;      //needed for interrupt to work
    CM1CON1bits.INTP=1; 	//set interrupt flag on positive going edge
    
    CM1CON0bits.EN=1;   	//enable comparator 1

    // ____________________ INITIALISING FALLING EDGE COMPARATOR: CM12
    
    CM2NCHbits.NCH=0b011; 	// pin RF7 as input for comparator
    CM2PCHbits.PCH=0b101;   //use DAC output for positive input
    CM2CON0bits.HYS=1;      //a little bit of hysteresis to stop multiple triggers
    CM2CON0bits.POL=1;      //needed for interrupt to work
    CM2CON1bits.INTN=1; 
    CM2CON0bits.EN=1;   	//enable comparator 1
    
    DAC_init();				//initialise the DAC

    
}
