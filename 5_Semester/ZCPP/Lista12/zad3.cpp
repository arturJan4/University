#include <iostream>

/*
 * GCD using metaprogramming (recursive formula - Euclidean algorithm)
 * if (b == 0) -> return a
 * else return GCD(b, a % b);
 */

template<int A, int B>
struct GCD {
    static constexpr int value = GCD<B, A % B>::value;
};

template<int A>
struct GCD<A, 0> {
    static constexpr int value = A;
};

int main()
{;
    static_assert(GCD<20, 35>::value == 5);
    static_assert(GCD<35, 20>::value == 5);
    static_assert(GCD<34, 12>::value == 2);
    static_assert(GCD<5, 7>::value == 1);
    static_assert(GCD<1, 100>::value == 1);
    static_assert(GCD<100, 1>::value == 1);
    static_assert(GCD<114, 1242>::value == 6);
    static_assert(GCD<256, 2048>::value == 256);
    static_assert(GCD<2048, 256>::value == 256);

    return 0;
}
