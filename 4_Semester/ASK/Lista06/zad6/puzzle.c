#include <stddef.h>
#include <stdint.h>
    
    void readlong(long *x);

    long puzzle5(void)
    {
        long a, b;
        readlong(&a);
        readlong(&b);
        return (a % b) == 0;
    }