#pragma once
#include <vector>
#include <array>
#include <utility>

inline std::vector<double> linspace(const double min, const double max, const int nodes)
{
    const double step = (max - min)/(nodes - 1);
    
    std::vector<double> space(nodes);
    space[0] = min;

    for(int i=1; i<nodes; i++)
    {
        space[i] = space[i - 1] + step;
    }

    return space;
}

inline std::array<std::vector<std::vector<double>>, 2> meshgrid(const std::vector<double>& x, const std::vector<double>& y)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int xsize = static_cast<int>(x.size());
    const int ysize = static_cast<int>(y.size());

    Matrix X(ysize, Vector(xsize));
    Matrix Y(ysize, Vector(xsize));

    for (int i = 0; i < ysize; i++)
    {
        X[i] = x;
    }

    for (int i = 0; i < ysize; i++)
    {
        for (int j = 0; j < xsize; j++)
        {
            Y[i][j] = y[i];
        }
    }

    return {std::move(X), std::move(Y)};
}

inline std::vector<double> ravel(const std::vector<std::vector<double>>& M)
{
    const int xsize = static_cast<int>(M[0].size());
    const int ysize = static_cast<int>(M.size());
    const int size = xsize*ysize;

    std::vector<double> v(size);

    for(int i=0; i<ysize; i++)
    {
        for(int j=0; j<xsize; j++)
        {
            v[j + xsize*i] = M[i][j];
        }
    }

    return v;

}

inline std::vector<double> matmul(const std::vector<std::vector<double>>& A, const std::vector<double> x)
{

    const int cols = static_cast<int>(A[0].size());
    const int rows = static_cast<int>(A.size());

    std::vector<double> b(rows, 0.0);

    for(int i=0; i<rows; i++) 
    {
        for(int j=0; j<cols; j++)
        {
            b[i] += A[i][j]*x[j];
        } 
    }

    return b;

}


inline std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int Acols = static_cast<int>(A[0].size());
    const int Arows = static_cast<int>(A.size());

    const int Bcols = static_cast<int>(B[0].size());
    const int Brows = static_cast<int>(B.size());

    Matrix C(Arows, Vector(Bcols, 0.0));

    for (int i = 0; i < Arows; i++)
    {
        for (int j = 0; j < Bcols; j++)
        {
            for (int k = 0; k < Acols; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

