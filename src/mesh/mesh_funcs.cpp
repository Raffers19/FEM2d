#include "mesh/mesh_funcs.hpp"
#include <vector>
#include <array>
#include "core_funcs.hpp"

std::array<std::vector<double>, 2> gridToNode(const std::array<std::vector<std::vector<double>>, 2>& V)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int xsize = static_cast<int>(V[0][0].size());
    const int ysize = static_cast<int>(V[0].size());
    const int Nnodes = xsize*ysize;

    std::vector<double> xn(Nnodes);
    std::vector<double> yn(Nnodes);

    for(int i=0;i<ysize;i++)
    {
        for(int j=0;j<xsize;j++)
        {
            xn[i*xsize + j] = V[0][i][j];
            yn[i*xsize + j] = V[1][i][j];
        }
    }

    std::array<std::vector<double>, 2> A{xn, yn};

    return A;
} 

std::array<std::vector<int>, 3> constructConnectivity(const int Nx, const int Ny)
{
    int squares = (Nx - 1)*(Ny - 1);
    int tn = 2*squares;

    std::vector<int> a(tn), b(tn), c(tn);

    for(int i=0; i<Ny-1; i++)
    {
        for(int j=0; j<Nx-1; j++)
        {
            int ind = 2*(j+i*(Nx-1));

            if ((i+j) % 2 == 0)
            {
                a[ind] = j + Nx*i;
                b[ind] = (j+1) + Nx*i;
                c[ind] = (j+1) + Nx*(i+1);

                a[ind+1] = j + Nx*i;
                b[ind+1] = (j+1) + Nx*(i+1);
                c[ind+1] = j + Nx*(i+1);
            }
            else
            {
                a[ind] = j + Nx*i;
                b[ind] = (j+1) + Nx*i;
                c[ind] = j + Nx*(i+1);

                a[ind+1] = (j+1) + Nx*i;
                b[ind+1] = (j+1) + Nx*(i+1);
                c[ind+1] = j + Nx*(i+1);
            }

        }

    }

    std::array<std::vector<int>, 3> con{a, b, c};

    return con;
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
