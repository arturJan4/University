#include "Matrix.hpp"
#include <random>
#include <iostream>
#include <utility>

double Matrix::randomDouble(double low, double high)
{
    static std::random_device seed;
    static std::mt19937 gen{seed()}; // seed

    return std::uniform_real_distribution<double>{low, high}(gen);
}

Matrix::Matrix(u_int64_t size)
: Matrix(size, size)
{}


Matrix::Matrix(u_int64_t rows, u_int64_t cols)
{
    m_rows = rows;
    m_cols = cols;
    m_matrix.resize(rows);

    for (uint64_t i = 0; i < rows; i++)
    {
        m_matrix[i].resize(cols, 0);
    }
}

Matrix::Matrix(const std::vector<std::vector<double>>& vec)
{
    m_matrix = vec;
    m_rows = m_matrix.size();
    if(m_rows != 0)
        m_cols = m_matrix[0].size();
    else
        m_cols = 0;
}


Matrix Matrix::operator*(Matrix& sec)
{
    if (this->m_cols != sec.m_rows)
    {
        throw std::invalid_argument("wrong matrix dimensions");
    }

    uint64_t newRows = this->m_rows;
    uint64_t newCols = sec.m_cols;

    Matrix result(newRows, newCols);

    for (uint64_t i = 0; i < newRows; i++)
    {
        for (uint64_t j = 0; j < newCols; j++)
        {
            double sum = 0.0;
            // dot product
            for (uint64_t k = 0; k < m_cols; k++)
            {
                sum += m_matrix[i][k] * sec(k, j);
            }

            result(i, j) = sum;
        }
    }

    return result;
}

Matrix Matrix::randomize(double low, double high)
{
    for (uint64_t i = 0; i < m_rows; i++)
    {
        for (uint64_t j = 0; j < m_cols; j++)
        {
            m_matrix[i][j] = randomDouble(low, high);
        }
    }
    return *this;
}

Matrix Matrix::square()
{
    // matrix must be square
    if (m_cols != m_rows)
    {
        throw std::invalid_argument("wrong matrix dimensions");
    }

    return (*this * *this);
}

void Matrix::print()
{
    for (uint64_t i = 0; i < m_rows; i++)
    {
        for (uint64_t j = 0; j < m_cols; j++)
        {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

double &Matrix::operator()(u_int64_t &r, u_int64_t &c)
{
    return this->m_matrix[r][c];
}

u_int64_t Matrix::getMRows() const
{
    return m_rows;
}

u_int64_t Matrix::getMCols() const
{
    return m_cols;
}
