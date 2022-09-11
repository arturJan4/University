#include <stddef.h>
#include <limits.h>
    struct T 
    {
        long min;
        long max;
        long average;
    };

    struct T puzzle(long *a, long n) 
    {
        long sum = 0;
        long max = LONG_MIN;
        long min = LONG_MAX;
    
        for(long temp = 0; temp < n; temp++) 
        {
            long elem = a[temp];
            if (elem < min) 
                min = elem;
            if (elem > max) 
                max = elem;
            sum += elem;
        }
    
        struct T t;
        t.min = min;
        t.max = max;
        t.average = (sum / n);

        return t;
    }