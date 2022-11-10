#ifndef _interrupts_H
#define _interrupts_H

#include <xc.h>

#define _XTAL_FREQ 64000000

unsigned int Interrupts_init();
unsigned int __interrupt(high_priority) HighISR();
void __interrupt(low_priority) LowISR();


#endif
