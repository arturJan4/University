#include <iostream>
#include <ratio>

// harmonic series using metaprogramming

template <int N> struct harmonic_series
: std::ratio_add<std::ratio<1, N>, harmonic_series<N-1>>
{
};

template <> struct harmonic_series<1>
: std::ratio<1, 1>
{
};

int main()
{
   using start = harmonic_series<47>;

   // 10 -> 7381/2520 -> działa
   // 40 -> 2078178381193813/485721041551200 -> działa
   // 46 -> 5943339269060627227/1345655451257488800 -> działa
   // 47 -> /usr/include/c++/9/ratio:450:47: error: static assertion failed: overflow in addition
   // numerator and denominator are std::intmax_t

   std::cout << start::num << "/" << start::den << "\n";

    return 0;
}