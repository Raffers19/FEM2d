#include "quadrature/quad.hpp"
#include "quadrature/quad_funcs.hpp"
#include "core_funcs.hpp"
#include <vector>
#include <array>

Quadrature::Quadrature(int quadOrder)
    : order{quadOrder}
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Vector nodes1d = legaussNodes(order);
    Vector weights1d = legaussWeights(nodes1d);

    refNodes = duffyNodes(nodes1d);
    refWeights = duffyWeights(nodes1d, weights1d);
}

std::vector<std::vector<double>> Quadrature::getLocalStiff(double x1,double x2,double x3,double y1,double y2,double y3, int p) const
{
    std::vector<std::vector<double>> L = computeLocalStiff(p, refNodes, refWeights, x1, x2, x3, y1, y2, y3);
    return L;
}




