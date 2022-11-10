#include <xc.h>
#include "time_sync_file.h"


//In depth explanation of this function can be found in the ReadMe file
unsigned int time_sync(unsigned int date, unsigned int month, unsigned int hour, unsigned int minutes, unsigned int led_value){
    
    unsigned int led_old = 0;    //Tracks LED state from previous minute
    unsigned int led_new = 0;   //Tracks LED state from current minute
    
    
    if ((date==16)&&(month==3)&&(hour==6)&&(minutes>0)&&(minutes<24)){      //Checks if it is the 16th of March in between 6:00 and 6:24 (we expect the sunrise to happen at 6:12 so can assume LED will change state within this range)
        
        led_old = led_new;      //The previously recorded LED value becomes the old value
        led_new = led_value;    //Current LED value is updated
        
        if (led_old != led_new) {   //Compares old and new LED values, if they are different then sunrise has occurred.
            minutes = 12;           //Update minutes to 12 which corresponds to the actual sunrise time in London on the 16th of March
            return minutes;         //Return minutes to the main file so that they can be updated to be synchronous with the sun
        
        }        
    }
    
    if ((date==16)&&(month==10)&&(hour==7)&&(minutes>10)&&(minutes<34)){        //Checks if it the 16th of October in between 7:10 and 7:34, we expect sunrise to happen at 7:22]
        
        led_old = led_new;
        led_new = led_value;
        
        if (led_old != led_new) {
            minutes = 22;
            return minutes; //Return minutes to the main file as explained above
  
        }        
    
    }
    
    return minutes;
}


