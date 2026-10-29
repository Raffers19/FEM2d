#pragma once
#include <vector>
#include <array>
#include <utility>
#include <stdexcept>

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

inline std::vector<std::vector<double>> inverse(const std::vector<std::vector<double>>& A)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const std::size_t n = A.size();

    for (const auto& row : A)
    {
        if (row.size() != n)
        {
            throw std::invalid_argument("Matrix must be square");
        }
    }

    // Copy A and initialize the identity matrix
    Matrix M = A;
    Matrix B(n, Vector(n, 0.0));

    for (std::size_t i = 0; i < n; i++)
    {
        B[i][i] = 1.0;
    }

    // Gauss-Jordan elimination
    for (std::size_t i = 0; i < n; i++)
    {
        // Find the row with the largest pivot
        std::size_t pivot = i;

        for (std::size_t j = i + 1; j < n; j++)
        {
            if (std::abs(M[j][i]) > std::abs(M[pivot][i]))
            {
                pivot = j;
            }
        }

        // Check for singularity
        if (std::abs(M[pivot][i]) <=
            std::numeric_limits<double>::epsilon())
        {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        // Swap rows
        std::swap(M[i], M[pivot]);
        std::swap(B[i], B[pivot]);

        // Normalize pivot row
        const double pivotValue = M[i][i];

        for (std::size_t j = 0; j < n; j++)
        {
            M[i][j] /= pivotValue;
            B[i][j] /= pivotValue;
        }

        // Eliminate all other entries in column i
        for (std::size_t k = 0; k < n; k++)
        {
            if (k == i)
            {
                continue;
            }

            const double factor = M[k][i];

            for (std::size_t j = 0; j < n; j++)
            {
                M[k][j] -= factor * M[i][j];
                B[k][j] -= factor * B[i][j];
            }
        }
    }

    return B;
}

inline std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& A)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const std::size_t rows = A.size();
    const std::size_t cols = A[0].size();

    Matrix B(cols, Vector(rows));

    for (std::size_t i = 0; i < rows; i++)
    {

        for (std::size_t j = 0; j < cols; j++)
        {
            B[j][i] = A[i][j];
        }
    }

    return B;
}

inline std::vector<std::vector<double>> transinv(const std::vector<std::vector<double>>& A)
{
    std::vector<std::vector<double>> T = transpose(A);
    std::vector<std::vector<double>> IT = inverse(T);  

    return IT;
}

inline double determinant(const std::vector<std::vector<double>>& A)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const std::size_t n = A.size();

    if (n == 0)
    {
        throw std::invalid_argument("Matrix is empty");
    }

    for (const auto& row : A)
    {
        if (row.size() != n)
        {
            throw std::invalid_argument("Matrix must be square");
        }
    }

    // Copy the matrix to avoid modifying A
    Matrix M = A;

    double det = 1.0;

    for (std::size_t i = 0; i < n; i++)
    {
        // Find the largest pivot in column i
        std::size_t pivot = i;

        for (std::size_t j = i + 1; j < n; j++)
        {
            if (std::abs(M[j][i]) > std::abs(M[pivot][i]))
            {
                pivot = j;
            }
        }

        // A zero pivot means the matrix is singular
        if (M[pivot][i] == 0.0)
        {
            return 0.0;
        }

        // Swap rows if necessary
        if (pivot != i)
        {
            std::swap(M[i], M[pivot]);
            det = -det;
        }

        const double pivotValue = M[i][i];

        det *= pivotValue;

        // Eliminate entries below the pivot
        for (std::size_t j = i + 1; j < n; j++)
        {
            const double factor = M[j][i] / pivotValue;

            for (std::size_t k = i + 1; k < n; k++)
            {
                M[j][k] -= factor * M[i][k];
            }

            M[j][i] = 0.0;
        }
    }

    return det;
}

inline double sum(const std::vector<double>& x)
{
    const int size = static_cast<int>(x.size());

    double s{0.0};

    for(int i=0; i<size; i++)
    {
        s += x[i];
    }

    return s;
}

inline double sum(const std::vector<std::vector<double>>& x)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int rows = static_cast<int>(x.size());
    const int cols = static_cast<int>(x[0].size());

    double s{0.0};

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            s += x[i][j];
        }
    }
    return s;
}

inline std::vector<double> sum(const std::vector<std::vector<double>>& x, int axis)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int rows = static_cast<int>(x.size());
    const int cols = static_cast<int>(x[0].size());

    Vector s;

    if(axis==0)
    {
        s.resize(cols);    
        
        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                s[i] += x[j][i]; 
            }
        }

    }else if(axis==1)
    {
        s.resize(rows); 
        
        for(int i=0; i<rows; i++)
        {
            s[i] = sum(x[i]);
        }

    }

    return s;
}

inline double dot(const std::vector<double>& x, const std::vector<double>& y)
{
    const int len = static_cast<int>(x.size());

    double s{0.0};

    for(int i=0; i<len; i++)
    {
        s += x[i]*y[i];
    }

    return s;
}

inline std::vector<double> dot(const std::vector<std::vector<double>>& x, const std::vector<std::vector<double>>& y)
{

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int rows = static_cast<int>(x.size());
    const int cols = static_cast<int>(x[0].size());

    Matrix full(rows, Vector(cols));

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            full[i][j] = x[i][j]*y[i][j];
        }
    }

    Vector dotprod = sum(full, 0);
    return dotprod;    
}