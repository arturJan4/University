#include <iostream>

template<size_t N>
double inner(double *x, double *y)
{
    double sum = 0;

    for (size_t i = 0; i < N; ++i)
    {
        sum += (*x * *y);
        x++;
        y++;
    }

    return sum;
}

template<size_t N, typename T = double>
T _inner(T *x, T *y)
{
    T sum = 0;

    for (size_t i = 0; i < N; ++i)
    {
        sum += (*x * *y);
        x++;
        y++;
    }

    return sum;
}

int main()
{
    double vec1[4] = {2.0, 3.0, 4.0, 5.0};
    double vec2[4] = {1.0, 2.0, 1.0, 2.0};

    std::cout << inner<4>(vec1, vec2) << "\n";
    std::cout << inner<1>(vec1, vec2) << "\n";
    std::cout << inner<3>(vec1, vec2) << "\n";

    std::cout << _inner<4, double>(vec1, vec2) << "\n";

    return 0;
}
