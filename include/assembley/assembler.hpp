#pragma once
#include <array>
#include <vector>
#include "quadrature/quad.hpp"

class Assembler
{
private:
    std::array<std::vector<double>, 2> nodes;
    std::array<std::vector<int>, 3> con;

public:
    Assembler(
        const std::array<std::vector<double>, 2> nodalArray,
        std::array<std::vector<int>, 3> connectivityArray
    );

    std::vector<std::vector<double>> poissonStiffnessP1();

    template<typename Func>
    std::vector<double> poissonSourceP1(Func func);

    std::vector<std::vector<double>> boundaryDirichletH(const std::vector<std::vector<double>>& A, const std::vector<int>& bnodes);

    std::vector<double> boundaryDirichletH(const std::vector<double>& F, const std::vector<int>& bnodes);


};
template<typename Func>
std::vector<double> Assembler::poissonSourceP1(Func func)
{
    using Vector = std::vector<double>;

    const int p = 1;
    const int order = p + 2;

    Quadrature quad(order);

    const std::size_t tt = con[0].size();
    const std::size_t bn = nodes[0].size();

    Vector F(bn, 0.0);

    for (std::size_t n = 0; n < tt; n++)
    {
        const std::array<int, 3> tcon{
            con[0][n],
            con[1][n],
            con[2][n]
        };

        const double x1 = nodes[0][tcon[0]];
        const double x2 = nodes[0][tcon[1]];
        const double x3 = nodes[0][tcon[2]];
        const double y1 = nodes[1][tcon[0]];
        const double y2 = nodes[1][tcon[1]];
        const double y3 = nodes[1][tcon[2]];

        const Vector local = quad.getLocalSource(
            func, x1, x2, x3, y1, y2, y3, p
        );

        // Local basis order corresponds to vertices 2, 1, 3.
        const std::array<int, 3> dof{
            tcon[1],
            tcon[0],
            tcon[2]
        };

        for (std::size_t j = 0; j < 3; j++)
        {
            F[dof[j]] += local[j];
        }
    }

    return F;
}