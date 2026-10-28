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



