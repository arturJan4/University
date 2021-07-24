#include <algorithm>
#include <cstdio>
#include <vector>

int main()
{
    typedef std::pair<long long, long long> Pair;

    long long m = 0;
    long long d = 0;
    long long n = 0;
    long long sum = 0;
    std::vector<Pair> ropes; // <length, number>
    scanf("%lld", &m);
    
    ropes.reserve(m);

    for(long long i = 0; i < m; ++i)
    {
        scanf("%lld %lld", &d, &n);
        ropes.push_back(std::make_pair(d, n));
    }
    std::sort(ropes.begin(), ropes.end());
    
    for(long long i = 0; i < m; ++i)
    {
        while(ropes[i].second != 0)
        {
            if(ropes[i].second & 1) // odd number of ropes
            {
                ++sum;
                ropes[i].second -= 1;
                
                if(ropes[i].second == 0)
                    break;
            }
            
            ropes[i].second >>= 1; // half the number of ropes 
            long long doubleLength = (ropes[i].first << 1);
            Pair val = std::make_pair(doubleLength, 0);
            auto found = std::lower_bound(ropes.begin() + i, ropes.end(), val,          // bin search
                [](Pair lhs, Pair rhs) -> bool {return lhs.first < rhs.first;});
            ropes[i].first = doubleLength;

            if((*found).first == val.first)
            {
                (*found).second += ropes[i].second;
                break;
            }
        }
    }
    
    printf("%lld", sum);
    return 0;
}