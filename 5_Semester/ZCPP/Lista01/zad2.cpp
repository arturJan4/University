#include <iostream>

int main()
{
    std::cout <<R"foo(Instytut Informatyki Uniwersytetu Wrocławskiego
Fryderyka Joliot-Curie 15
50-383 Wrocław
)foo";

    std::cout <<R"foo(C:\Program Files\
)foo";

    std::cout <<R"foo(("))""(()"")")"()")(())))(()"
)foo";

    return 0;
}
