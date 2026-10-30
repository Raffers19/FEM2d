#include "assembley/assembler.hpp"
#include "quadrature/quad.hpp"
#include "core_funcs.hpp"

Assembler::Assembler(const std::array<std::vector<double>, 2> nodalArray, std::array<std::vector<int>, 3> connectivityArray)
    : nodes{nodalArray}, con{connectivityArray}
{

}

std::vector<std::vector<double>> Assembler::poissonStiffnessP1()
{

    int p = 1;
    int order = p + 2;

    Quadrature quad(order);

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;


    int tt = static_cast<int>(con[0].size()); 
    int bn = static_cast<int>(nodes[0].size());

    Matrix A(bn, Vector(bn));

    for (int n = 0; n < tt; n++)
    {
        const std::array<int, 3> tcon{con[0][n], con[1][n], con[2][n]};

        const double x1 = nodes[0][tcon[0]];
        const double x2 = nodes[0][tcon[1]];
        const double x3 = nodes[0][tcon[2]];
        const double y1 = nodes[1][tcon[0]];
        const double y2 = nodes[1][tcon[1]];
        const double y3 = nodes[1][tcon[2]];

        const Matrix L = quad.getLocalStiff(x1, x2, x3, y1, y2, y3, p);

        const std::array<int, 3> dof{tcon[1], tcon[0], tcon[2]};

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                A[dof[i]][dof[j]] += L[i][j];
            }
        }
    }

    return A;

}

std::vector<std::vector<double>> boundaryDirichletH(const std::vector<std::vector<double>>& A, const std::vector<int>& bnodes)
{
    int sizeA = static_cast<int>(A.size());
    int sizebc = static_cast<int>(bnodes.size());
    std::vector<std::vector<double>> D = A;

    for (int i=0; i<sizebc; i++)
    {
        for(int j=0; j<sizeA; j++)
        {
            D[bnodes[i]][j] = 0.0;
            D[j][bnodes[i]] = 0.0;
        }
        D[bnodes[i]][bnodes[i]] = 1.0;
    }

    return D;
}

std::vector<double> boundaryDirichletH(const std::vector<double>& F, const std::vector<int>& bnodes)
{
    //int sizeA = static_cast<int>(F.size());
    int sizebc = static_cast<int>(bnodes.size());

    std::vector<double> D = F;

    for (int i=0; i<sizebc; i++)
    {
        D[bnodes[i]] = 0.0;
    }

    return D;
}