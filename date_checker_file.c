#include <xc.h>
#include "date_checker_file.h"


unsigned int date_checker_function(unsigned int date, unsigned int month, unsigned int leap){
    
    if ((date>(28+leap)) && (month == 2)){   // if date is feb 28/29th on a leap year:
        date = 1;      // date is reset to 1. date is returned at the end of function to main.c
    }  

    if (((month == 4) || (month ==6) || (month ==9) || (month ==11))  && (date>30)){
                            // date reset for when date is 30th and month is april, june, sept, nov
        date = 1;
    }

     if (((month == 1) || (month ==3) || (month ==5) || (month ==7) || (month ==8) || (month ==10))  && (date>31)){
                            // date reset for when date is 31st and month is jan, march, may, july, aug, oct (NOT DECEMBER BECAUSE THAT IS IN MAIN.C)
        date = 1;
    }
    return date; // return new date. ie. date is updated
    
    
}



