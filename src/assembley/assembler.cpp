#include "assembley/assembler.hpp"
#include "quadrature/quad.hpp"

Assembler::Assembler(const std::array<std::vector<double>, 2> nodalArray, std::array<std::vector<int>, 3> connectivityArray)
    : nodes{nodalArray}, con{connectivityArray}
{

}

std::vector<std::vector<double>> Assembler::poissonStiffness1d()
{

    int p = 1;
    int order = p + 2;

    Quadrature quad(order);

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;


    int tt = static_cast<int>(con[0].size()); 
    int bn = ((p + 1)*(p + 2))/2;

    Matrix A(bn, Vector(bn));

    for(int i=0; i<tt; i++)
    {
        double x1 = nodes[0][con[0][i]];
        double x2 = nodes[0][con[1][i]];
        double x3 = nodes[0][con[2][i]];
        double y1 = nodes[1][con[0][i]];
        double y2 = nodes[1][con[1][i]];
        double y3 = nodes[1][con[2][i]];

        Matrix L = quad.getLocalStiff(x1, x2, x3, y1, y2, y3, p);
    }


}