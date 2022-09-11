#include <iostream>

// Lucas numbers using metaprogramming (recursive formula)

template<int N>
struct Lucas {
    static constexpr int value = Lucas<N-1>::value + Lucas<N-2>::value;
};

template<>
struct Lucas<0> {
    static constexpr int value = 2;
};

template<>
struct Lucas<1> {
    static constexpr int value = 1;
};

int main()
{;
    static_assert(Lucas<0>::value == 2);
    static_assert(Lucas<1>::value == 1);
    static_assert(Lucas<2>::value == 3);
    static_assert(Lucas<7>::value == 29);
    static_assert(Lucas<19>::value == 9349);

    return 0;
}
