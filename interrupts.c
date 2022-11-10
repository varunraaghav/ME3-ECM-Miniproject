#include <xc.h>
#include "interrupts.h"
#include "LEDarray.h"

extern int time;  // global variable
//extern int test_mode;

unsigned int Interrupts_init()
{
    
    PIE2bits.C1IE=1; 	//enable interrupt source INT0   ie = interrupt enabled (for DAC))
    PIE2bits.C2IE=1; // 2nd DAC interrupt (rising edge and falling edge. 2 seperate interrupts for more robust application)

    PIE0bits.TMR0IE=1; // enable input source (PIE enable) as TMR0 register
    
    INTCONbits.GIEL=1;  // turns on low prio interrupts
    INTCONbits.IPEN=1;   //multiple priority levels
    
    IPR2bits.C1IP=0;   /// iP =  interrupt priority (1 = high, 0 = low)   DAC is assigned as LowPriority as time_of_day value supercedes LDR input (corresponding to 1 and 5am requirements)
    IPR2bits.C2IP=0; // iP for 2nd comparator

    IPR0bits.TMR0IP=1;  // im assigning tmr0 as high priority input


    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)    

    
}


unsigned int __interrupt(high_priority) HighISR()
{
    
    if(PIR0bits.TMR0IF){ 					//check the interrupt source: tmr0
        
        time = time + 1;
                
        PIR0bits.TMR0IF=0; 						//clear the interrupt flag!
        TMR0H=0b00001011;    //write High reg first, update happens when low reg is written to
        TMR0L=0b11011100;    // starting off at 3036 to get exactly 1 second
        
    }
}

void __interrupt(low_priority) LowISR(){
    
    
    if(PIR2bits.C1IF){ 					//check the interrupt source: CM1 - DAC RISING EDGE
    
        LATHbits.LATH3 = 1;   // setting rh3 led to 1 if rising
        PIR2bits.C1IF=0;  // clearing interrupt flag
        
    }
    
    if(PIR2bits.C2IF){ 					//check the interrupt source: CM2 - DAC FALLING EDGE
    
        LATHbits.LATH3 = 0;    // setting rh3 led to 0 if falling
        PIR2bits.C2IF=0;    
        
    }
    
    // although this takes up more lines of code than simply having 1 comparator and toggling led states, it is more robust as it desginates a unique task as per comparator instruction. therefore, even if pickit is reset in dark conditions, led states wont be swtiched
}