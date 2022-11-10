#include <stdio.h>

#include "LCD_print_file.h"
#include "LCD.h"


void LCD_print_function(unsigned int date, unsigned int month, unsigned int year, unsigned int day){
    
    LCD_clear();              // clear previous date function, called in LCD.c file 
    
    LCD_sendstring("Date: ");  // for formatting
    
    
    char str1[2];                     // print date of month as string
    sprintf(str1, "%i", date);
    LCD_sendstring(str1);  // send_string function called
    
    LCD_sendstring("/");    // universal date formatting
    
    char str2[2];
    sprintf(str2, "%i", month);   // print month as string
    LCD_sendstring(str2);
    
    LCD_sendstring("/");

    char str3[4];
    sprintf(str3, "%i", year);    // print year as string
    LCD_sendstring(str3);
    
    
    LCD_setline(2);  // set LCD output to 2nd line

    if (day==0){                            // if statements used to print the day of the week on the 2nd line of LCD based on "day" variable inserted into LCD_print_function
        LCD_sendstring("Day: Sunday");
    } else if (day==1){
        LCD_sendstring("Day: Monday");
    } else if (day==2){
        LCD_sendstring("Day: Tuesday");
    } else if (day==3){
        LCD_sendstring("Day: Wednesday");
    } else if (day==4){
        LCD_sendstring("Day: Thursday");
    } else if (day==5){
        LCD_sendstring("Day: Friday");
    } else if (day==6){
        LCD_sendstring("Day: Saturday");
    }

}
