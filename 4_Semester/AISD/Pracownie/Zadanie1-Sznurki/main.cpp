#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    typedef std::pair<long long, long long> Pair;

    long long m,d,n;
    long long sum = 0;
    std::vector<Pair> ropes; // <length, number>
    std::cin >> m;
    ropes.reserve(m);

    for(long long i = 0; i < m; ++i)
    {
        std::cin >> d >> n;

        ropes.push_back(std::make_pair(d, n));
    }
    std::sort(ropes.begin(), ropes.end());
    
    for(long long i = 0; i < m; ++i)
    {
        while(ropes[i].second != 0)
        {
            if(ropes[i].second % 2) // odd number of ropes
            {
                ++sum;
                ropes[i].second -= 1;
                
                if(ropes[i].second == 0)
                    break;
            }
            
            ropes[i].second /= 2; // half the number of ropes 
            long long doubleLength = ropes[i].first * 2;
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
    
    std::cout << sum;
    return 0;
}