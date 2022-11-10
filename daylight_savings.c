#include <xc.h>
#include "daylight_savings.h"



extern int time;
unsigned int daylight_s(unsigned int date, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes, unsigned int BST, unsigned int test_mode){
    
    
    
    if ((date>=24) && (date <= 31) && (month == 3) && (day == 0) && (hour == 2) && (minutes==0) && (BST==0)){       //Checks if it is 2 am on the last Sunday of March
        if (test_mode ==1){
            time = time + 1;    //Updates time in test mode as time corresponds to hours

        }     
        
        return 1; // time will be added by 1, corresponding to losing an hour in march                          
    }
           
    else if ((date>=24) && (date <= 31) && (month == 10) && (day == 0) && (hour == 2) && (minutes==0) && (BST==1)){ //Checks if it is the last Sunday of October at 2 am
                
        if (test_mode ==1){     //Updates time in test mode as time corresponds to hours
            time = time - 1;  // time is lost. needed for test mode to work

        }
        return -1; // time will be subtracted by 1, corresponding to gaining an hour in october
                
    }
    
    else {
        return 0;       //No change to daylight savings time needed
    }
    
}
