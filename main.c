#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)


#include <stdio.h>

#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "daylight_savings.h"
#include "leap_function.h"
#include "time_sync_file.h"
#include "energy_savings_file.h"
#include "date_checker_file.h"
#include "month_checker_file.h"
#include "LCD.h"
#include "LCD_print_file.h"


#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

int time = 0b0; //Corresponds to real life seconds, GLOBAL VARIABLE (ONLY 1 USED IN ENTIRE PROJECT)

int main(void) {

    // date = Friday 28th February 2020

    unsigned int date = 26; //Day of the month, e.g. for January it will be between 1-31
    unsigned int month = 3;    //Index value for month, January = 1, February = 2, March = 3 ...
    unsigned int year = 2022;   //Index value for year
    
    unsigned int leap = 0;      //If leap year =1 , if not ;eap year = 0
    unsigned int day = 6;       //Day of the week, Sunday = 0, Monday = 1, Tuesday = 2...
    unsigned int BST = 0; // manually input if you're in summer time or winter time)
    
    unsigned int test_mode = 1; //In test mode hours last 1 second so that we can create a video to display the LED working in real time
    
    unsigned int hour = 0b0;    //Binary number that tracks the hour
    unsigned int minutes = 0;   //Tracks minutes, range (0-59)
    
    unsigned int daylight_adjustment = 0;   //Integer value that states how much time needs to be adjusted for daylight savings, =1,-1 or 0
    unsigned int led_value = 0;  //integer value used to check LATHbits.LATH3 output state, and inserted into time_sync function
    
    
    Comp1_init();   //Initialise comparator function
    LEDarray_init(); //Initialise LEDarray_disp function
    Timer0_init();  //Initialise timer function
    Interrupts_init();  //Initialise interupt function

    LATHbits.LATH3=0;    //LED initialisation
    TRISHbits.TRISH3=0;
    
    LCD_Init();     // initialise LCD function from lab 4
    LCD_setline(1);  // set LCD output to 1 line

    LCD_print_function(date, month, year, day);  // call LCD print function to display current date

    
    while (1){  // infinite while loop
                
         
//________________________ MAIN CODE computation: checking for test mode has to be done in main   ___________________________________________________________________________________________________
        if (test_mode == 1){    // checking for test_mode
             hour = time;  // test_mode condition
        } 
        else if (time==60){         // increasing minutes and hours proportionately according no. of seconds in a minute, and minutes in an hour
            minutes = minutes + 1;
            time = 0;
            
            if (minutes == 60){
                hour = hour + 1;
                minutes = 0;
            }
        } 
// ______________________________________________________________________________________________________________________________ CANNOT BE MOVED FROM main.c
        
        if(hour==24){  // if statement to check if hour has reached 24, ie 1 day has passed: multiple resets need to be made at this point
            
            hour=0;  // hour of day is reset to 0. the Day_resetting is done in main.c file as separate function cannot return more than 1 value, and we only wanted 1 global variable
            time = 0;  // time (ie. seconds) is reset to 0. This is particularly useful in test mode. in normal mode, it will be 0 anyways
            
            date = date + 1;  // date of the month is increased by 1 at the end of the day
            day = (day + 1)%7; // day of the week is increased by 1 (within mod 7) where 0 is a sunday, 1 is monday, 6 is saturday 
            
            
            date = date_checker_function(date, month, leap);       // date_checker function to increase date value is based on months with 28,29,30 and 31 days (ie. leap value is inserted as well)
            month = month_checker_function(date, month, leap);     // month_checker function to increase value of month by 1 if end of month
            
            
            if (month==12 && date>31){   // if statement to check if specific date is dec 31st, 
                date = 1;               // this could be put into 2 separate function (ie to return year and date), but that would be inefficient to call the function at every instance
                month = 1;      
                year = year + 1;    // year increased by 1 at end of day of dec 31st
                
                leap = leap_func(year);  // leap function is called to see if the next year is a leap year

            }
            
            LCD_print_function(date, month, year, day);  // call LCD print function to display current date

        }
// IF TIME==24 STATEMENT ENDS HERE. ____________________________________________________________________________________________________         
        
        daylight_adjustment = daylight_s(date, month, day, hour, minutes, BST, test_mode); // daylight savings function called to output an integer value which is either 1 or -1 to see if hour needs to be adjusted accordingly
       
        hour = hour + daylight_adjustment;  // adjust hour according to daylight_s func
        BST = BST + daylight_adjustment;  // adjust time_zone accordingly as well
        
        energy_savings_function(hour);  // call energy savings function to stop LED being turned on regardless of LDR value between 1am and 5am
        

        if (test_mode==0){   // calling time_sync only if NOT in test mode
            led_value = LATHbits.LATH3;  // storing the current output state of the H3 light
            minutes = time_sync(date, month, hour, minutes, led_value); // calling time_sync function to adjust minutes according to sunrise (logic explained inside function)
        }
        
        LEDarray_disp_bin(hour);  // display hour of the day in binary in 8bit LED board. In test mode, it will display hours which is updated every second 
    }
    
// ________ end of infinite while loop ______________________________________________    

}