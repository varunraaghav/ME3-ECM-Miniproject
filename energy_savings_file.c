#include "energy_savings_file.h"
#include "comparator.h"


void energy_savings_function(unsigned int hour){
    
    if ((hour >=1) && (hour <5)){   // checks if time (ie. hour) is between 1 am and 5 am
            
            DAC1CON0bits.DAC1EN=0;      //turn off DAC in that time period, so that LED will not be turned on as comparator will not be running

    }
    else{
            
        DAC1CON0bits.DAC1EN=1;      //turn on DAC otherwise so that comparator function and LED are function normally
            
    }
}
