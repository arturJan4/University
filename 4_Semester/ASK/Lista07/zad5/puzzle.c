#include <stddef.h>

typedef struct A {
    long u[2];
    long *v;
} SA;
typedef struct B {
    long p[2];
    long q;
} SB;


    SB __attribute__((noinline)) eval(SA s)
    {
        long x=s.u[0], y=s.u[1], z=*s.v; 
        SB result = {
            .p[0] = z * x,
            .p[1] = x - z,
            .q = x - y
        };
        //ptr = &result;
        return result;
    }
    
    long wrap(long x, long y, long z)
    {
        SA temp = {
            .u[1] = y,
            .v = &z,
            .u[0] = x
        };
        
        SB sb = eval(temp);
        
        return (sb.p[1] + sb.p[0]) * sb.q;
    }
    