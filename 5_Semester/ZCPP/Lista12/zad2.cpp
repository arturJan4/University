#include <iostream>

/*
 * Binomial coefficient using metaprogramming (recursive formula)
 * if (k == 0 | k == 1) -> return 1
 * else return Bin(n-1, k-1) + Bin(n-1, k);
 */
template<int N, int K>
struct Bin {
    static constexpr int value = Bin<N-1, K-1>::value + Bin<N-1, K>::value;
};

template<int N>
struct Bin<N, 0> {
    static constexpr int value = 1;
};

template<int N>
struct Bin<N, N> {
    static constexpr int value = 1;
};

template<int N>
struct Bin<N, 1> {
    static constexpr int value = N;
};

template<>
struct Bin<0, 0> {
    static constexpr int value = 1;
};

int main()
{;
    static_assert(Bin<0,0>::value == 1);
    static_assert(Bin<1,0>::value == 1);
    static_assert(Bin<10,0>::value == 1);
    static_assert(Bin<10,10>::value == 1);
    static_assert(Bin<10,1>::value == 10);
    static_assert(Bin<10,2>::value == 45);
    static_assert(Bin<10,7>::value == 120);
    static_assert(Bin<25,12>::value == 5200300);

    return 0;
}
