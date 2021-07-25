
    long puzzle(long n, long *p)
    {
        long result = 0;
        if(n > 0)
        {
            long temp;
            result = puzzle(n * 2, &temp);
            result += temp;
            n += result;
        }
        *p = n;
        return result;
    }