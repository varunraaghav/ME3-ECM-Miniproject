# Mini project - Energy saving automatic outside light

## Explanation of Code

Task 1: The comparator connected to the LDR will trigger an interrupt when the voltage across the LDR goes above or below the threshold voltage. We have got two comparators, one rising and one falling, to account for the two different output states that the comparaotr can go between. The threshold voltage was calibrated in a prvevious lab. When the comparator interrupt is activated a signal is sent to the outout LED to change state.

Task 2: We use the Timer0 function from Lab 3. Everytime the timer overflows a second has passed and our time updates. In test mode, so that testing can be done at a rapid pace, one timer overflow corresponds to an hour. If test mode is not activated the timer functions in real time. From this we can work out the time of day and complete the remainings tasks. The hour is displayed in binary on the LED array board in a similar manner to Lab 2.

Task 3: When our hour variable is between 1 and 5 am we turn off the comparator so that the LED will always be off during this period. Once it has reached 5 am it is turned back on and the LED operates as usual.

Task 4: Given we have kept track of hours we then create new variables that keep track of: day of the week, day of the month, month and year. This allows us to know what the date is at any one time. Daylight savings gets updated on the last Sunday of March and October. We are constantly checking if we are in the last week of the month and if it is a Sunday. If so, at 2 am the hour gets updated to adjust for daylight savings. A new variable is also created called BST to keep track of timezone. Separate files check whether the month or day needs to be updatd and if the year is a leap year.

Task 5: To maintain time synchronicity we compare the sunrise time on two specific days of the year to when our LED changes state. We only check this twice as we do not expect the system to go very far out of sync with the sun and this function is merely a re-calibration by a few minutes. If the sunrise has not happened at the expected time, the clock is adjusted so that the sunrise happens at the pre-programmed time. 


##Explanation of the Functionality of Each File

LCD.C: File that initialises the LCD using the instructions from Lab 4.

LCD_print_file: Outputs the date on the LCD board

LEDarray: Initialises and outputs the hour on the LED array

Comparator: Codes the interrupts that get activated when the voltage across the LDR goes past the threshold.

Date_checker: Checks whether the day of the month has to be reset back to 1 when it is a new month. e.g. Prevents date going from January 31st to January 32nd and instead goes to January 1st. Month checker file updates the month.

Daylight_savings: Checks whether it is the last Sunday of March or October and if it is adjusts the time at 2 am to account for daylight savings. The variable BST keeps track of which timezone we are in. This is especially useful to prevent an infinite loop of time updates in October as the hour is constantly reversed at 2 am.

Energy_savings: Checks whether the time is between 1 and 5 am and turns off the DAC in this time period so that the LED will not be on.

Interrupts: Same use as Lab 2.

Leap_function: Used to work out if the new year is a leap year, only activated when the day switches from December 31st to January 1st.

Main: Updates hours and accordingly calls the necessary function to complete assignments.

Month_checker: Updates month when the day of the month resets. E.g. January 31st -> January 1st (via date_cheker) -> February 1st (via month_checker).

Time_sync: Compares when the LED changes state in the morning (from on to off) with scheduled sunrise times collated from the internet. Only done twice in the year as we do not expect it to go very out of sync over the course of the year. 

Timers: Counts from 3036 to 2^16 and then overflows back to 3036. There is 1 second between each overflow, this is used to simulate real life seconds (hours in test mode).






## Learning outcomes

The principal learning objectives for this project are:

- Implement a working microprocessor based system to achieve a more complex real world task
- Develop your ability to independently plan, organise and structure your code 
- Improve your grasp of the C language and writing your own functions

## Brief

Outside lights that respond to ambient light levels are commonplace (i.e. street lights, porch lights, garden lights etc). These types of lights switch on at dusk and then turn off at dawn. However, energy and money can be saved if these lights are switched off during the small hours of the morning (for example, between 1am and 5am), when there are very few people around. Many councils in the UK have implemented/trialled this idea for street lights (https://www.bbc.co.uk/news/uk-england-derbyshire-16811386). Your task is to use the knowledge of microcontrollers and hardware that you have gained in labs 1-3 from this module to develop a fully automated solution.

## Specification
Design and program a device that meets the following requirements:

1. Monitors light level with the LDR and turns on an LED in low light conditions (i.e. night-time) and off in bright conditions (i.e. daytime)
1. Displays the current hour of day on the LED array in binary
1. Turns the light off between approx. 1am and 5am
1. Adjusts for daylight savings time
1. Maintain synchronicity with the sun indefinitely
1. Be fully automatic (requires zero maintenance after installation)

Please use this GitHub repo to manage your software development and submit your mini project code.

## Supplementary information and help
At first the task may seem quite straightforward but there are several points that often prove more tricky. The first is how to test code during development? You could test in real world conditions but you would be limited to one test cycle per day and this would severely slow down your development and debugging progress. To get around this you could implement a "testing mode" and pretend that a day lasts 24 seconds. This could be done using a #define directive to switch between "normal" and "testing" modes for your code.

Adjusting for daylight savings time is not too tricky. The clocks always change (in the UK) on the last Sunday in March (they go forward an hour) and the last Sunday in October (they go back an hour). One method of achieving this is to initialise what day it is when device is first switched on (using manual input) and then keep track of the days that pass and what the day of the week it is. Another method might be to automatically figure out what time of year it is (see below). Also don't forget about leap years! 

No clock is perfect, they can all run slightly fast/slow and can by influenced be external factors such as temperature. Ultimately this will result in drift over time and eventually the time will drift so far out of sync with real time that it is meaningless. For the purposes of our device the main requirement is that it remains in sync with the sun. You could use light from the sun to keep your clock in sync. Although the length of daylight varies considerably during the year, the midpoint between dusk and dawn only varies by a few minutes. This is termed solar midnight approx. 12am or solar noon approx. 12pm. One method of staying in sync with the sun is to use the LDR and record/calculate when these times occur and adjust your clock accordingly. The length of daylight also tells us information about what time of year it is and can be used to help us know when to adjust for daylight savings time.

![Day length](gifs/day-length-london.jpg)
http://wordpress.mrreid.org/2010/10/31/why-change-the-clocks/





