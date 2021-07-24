// Artur Jankowski
// 317928
// KPO
#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long a,b;
    std::cin >> a >> b;
    for(long long i = ((a + 2020)/2021) * 2021; i <= b; i += 2021)
    {
        std::cout << i << " ";
    }
    return 0;
}