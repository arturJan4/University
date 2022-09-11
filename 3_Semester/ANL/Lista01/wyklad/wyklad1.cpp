#include <iostream>

int main(int argc, char const *argv[])
{
    double x = 2;
    while(1 != x + 1)
    {
        x /= 2;
    }
    std::cout << "finished x=" << x;
    return 0;
}
