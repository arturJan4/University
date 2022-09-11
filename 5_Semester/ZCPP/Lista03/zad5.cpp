#include <iostream>
#include <chrono>

#include "Matrix.hpp"

auto measureSquareTime(Matrix m)
{
    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    m.square();

    high_resolution_clock::time_point end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end-start);
}

void experiment_runner(uint64_t n, uint64_t iter)
{
    using namespace std::chrono;
    Matrix m = Matrix(n).randomize(0.5, 2.0);

    duration<double> time_span{};

    for (uint64_t i = 0; i < iter; ++i)
    {
        time_span += measureSquareTime(m);
    }

    std::cout << "Squaring " << n << "x" << n << " matrix took: " << ((time_span).count() / iter) << " seconds. \n";
}

int main()
{
    Matrix x = Matrix(2, 3);
    x.print();

    Matrix a = Matrix({{1, 2, 3}, {4, 5, 6}});
    Matrix b = Matrix({{7, 8}, {9, 10}, {11, 12}});
    Matrix c = a * b;
    c.print();

    Matrix to_sq = Matrix({{0.6, 0.3, 0.1}, {0.4, 0.7, 1.1}, {0.2, 1.0, 1.0}});
    to_sq.square().print();

    Matrix rnd = Matrix(5, 5).randomize(0.5, 2.0);
    rnd.print();

    experiment_runner(100, 100);
    experiment_runner(1000, 10);
    experiment_runner(10000, 1);

    /*
     * Squaring 100x100 matrix took: 0.0103578 seconds.
     * Squaring 1000x1000 matrix took: 15.5727 seconds.
     * Squaring 10000x10000 matrix took: ... seconds.
     * multiplying is O(n^3) here -> so about 1000 times more seconds
     */
    return 0;
}