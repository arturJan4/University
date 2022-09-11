#include <iostream>

auto lucas_number(uint32_t n)
{
    if (n == 0)
        return 2;

    if (n == 1)
        return 1;

    return lucas_number(n-1) + lucas_number(n-2);
}

int main()
{
    for (int i = 0; i < 12; ++i)
    {
        std::cout << lucas_number(i) << " ";
    }
    return 0;
}
