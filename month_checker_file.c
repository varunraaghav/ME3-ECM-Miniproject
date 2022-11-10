#include <xc.h>
#include "month_checker_file.h"

unsigned int month_checker_function(unsigned int date, unsigned int month, unsigned int leap){
    
    if (date==1)                   // since date_checker_func is called just before month_checker function, on the 1st of each month: increase a month value
    {
        month = month + 1;
        
    }
    return month;  // return value of month to main.c
    
}