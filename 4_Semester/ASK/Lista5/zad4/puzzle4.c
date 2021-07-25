#include <stddef.h>
#include <stdint.h>
    
int puzzle4(long *a, long v, uint64_t s, uint64_t e)
{
    uint64_t result = ((e - s) >> 1) + s;
    if(e >= s)
    {
        long temp = a[result];
        if(temp == v)
        {
            return result;
        }
        if(temp > v)
        {
            e = result - 1;
            return puzzle4(a,v,s,e);
        }
        
        s = result + 1;
        return puzzle4(a,v,s,e);
    }
    return -1;
}