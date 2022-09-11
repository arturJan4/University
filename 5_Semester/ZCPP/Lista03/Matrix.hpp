#ifndef LISTA3_MATRIX_HPP
#define LISTA3_MATRIX_HPP
#include <vector>

class Matrix {
private:
    u_int64_t m_rows = 0, m_cols = 0;
    std::vector<std::vector<double>> m_matrix;

    static double randomDouble(double low, double high);
public:
    Matrix() = default;
    explicit Matrix(u_int64_t size);
    Matrix(u_int64_t rows, u_int64_t cols);
    explicit Matrix(const std::vector<std::vector<double>>& vec);

    Matrix operator*(Matrix &);
    Matrix randomize(double low, double high);
    Matrix square();

    void print();
    u_int64_t getMRows() const;
    u_int64_t getMCols() const;

    double& operator()(u_int64_t & r, u_int64_t &c);

    ~Matrix()=default;
    Matrix& operator=(const Matrix&) = delete;
};

#endif //LISTA3_MATRIX_HPP
