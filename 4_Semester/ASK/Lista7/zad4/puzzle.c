union elem {
    struct {
        long *p;
        long y;
    } e1;
    
    struct {
        long x;
        union elem *next;
    } e2;
};

union elem* proc(union elem *x)
{
    union elem *next = x->e2.next;
    long p_val = *(next->e1.p);
    p_val = p_val - next->e1.y;
    x->e2.x = p_val;
    return next;
}
