#include <xc.h>
#include "leap_function.h"


unsigned int leap_func(unsigned int year){
    // Checks if it leap year according to leap year rules found on the internet ______________________________________________________________
    unsigned int leap = 0;

    if (year%400 == 0) {
    leap = 1;
    }
     else if (year%100 == 0) {
    leap = 0;
    }
    else if (year%4 == 0)   {
    leap = 1;
    }
    else {
    leap = 0;
    }
    
    return leap; // leap is returned to main.c
    // 0 is not a leap year, leap=1 means leap year
    // not using a bool variable saves memory as a 1 bit int is a far smaller value
}

