#include <iostream>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int a, b;
    std::cin >> a >> b;

    int arr[5];
    if(a - b > 0)
        std::swap(a,b);    

    for(; a <= b; ++a)
    {
        std::cout << a << "\n";
    }

    return 0;
}