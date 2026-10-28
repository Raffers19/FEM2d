#include "quadrature/quad.hpp"
#include "quadrature/quad_funcs.hpp"
#include "core_funcs.hpp"
#include <vector>
#include <array>

Quadrature::Quadrature(const std::array<std::vector<double>, 2>& nodal_array, const std::array<std::vector<int>, 3>& connectivity, int quadOrder)
    : nodes{nodal_array}, con{connectivity}, order{quadOrder}
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Vector nodes1d = legaussNodes(order);
    Vector weights1d = legaussWeights(nodes1d);

    refNodes = duffyNodes(nodes1d);
    refWeights = duffyWeights(nodes1d, weights1d);
}

std::vector<std::vector<double>> Quadrature::transformMatrix(const double x1, const double x2, const double x3, const double y1, const double y2, const double y3)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Matrix B(2, Vector(2));

    B[0][0] = x1 - x3;
    B[0][1] = x2 - x3;
    B[1][0] = y1 - y3;
    B[1][1] = y2 - y3;

    return B;
}

