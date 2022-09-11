#include <stddef.h>
#include <stdint.h>

long puzzle2(char *s, char *d)
{
    char* currentS = s;
    
    while(1)
    {
        char* currentD = d;
        char  currentDVal;
        do
        {            
            currentDVal = *currentD;
            currentD++;
            if(currentDVal == 0)
                return (long)(currentS - s);
        }
        while(*currentS != currentDVal);
        
        currentS++;
    }
}