#include "quadrature/quad_funcs.hpp"
#include "core_funcs.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <numbers>


double legpoly(int n, double t)
{
    if (n == 0) return 1.0;
    if (n == 1) return 2.0*t - 1.0;

    const double x = 2.0*t - 1.0;

    double p0 = 1.0;
    double p1 = x;

    for (int k = 1; k < n; k++)
    {
        double p2 = ((2*k + 1)*x*p1 - k*p0)/(k + 1);

        p0 = p1;
        p1 = p2;
    }

    return p1;
}

std::vector<double> legaussNodes(int n)
{
    std::vector<double> nodes(n);

    for (int i = 1; i <= n; i++)
    {
        double t = 0.5 * (1.0 - std::cos(
            std::numbers::pi * (i - 0.25) / (n + 0.5)
        ));

        for (int k = 0; k < 100; k++)
        {
            double pn = legpoly(n, t);
            double pn1 = legpoly(n - 1, t);

            double dpn = n * (pn1 - (2.0*t - 1.0)*pn)
                         / (2.0*t*(1.0 - t));

            double dt = pn / dpn;
            t -= dt;

            if (std::abs(dt) < 1e-14)
                break;
        }

        nodes[i - 1] = t;
    }

    return nodes;
}

std::vector<double> legaussWeights(const std::vector<double>& nodes)
{
    const int n = static_cast<int>(nodes.size());
    std::vector<double> weights(n);

    for (int i = 0; i < n; i++)
    {
        double t = nodes[i];
        double pn1 = legpoly(n - 1, t);

        weights[i] = 4.0*t*(1.0 - t) / (n*n*pn1*pn1);
    }

    return weights;
}

std::array<std::vector<double>, 2> duffyNodes(const std::vector<double>& nodes)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    std::array<Matrix, 2> V = meshgrid(nodes, nodes);
    Vector xx = ravel(V[0]);
    Vector y = ravel(V[1]);
    Vector yy(y.size());

    for(std::size_t i=0; i<y.size(); i++)
    {
        yy[i] = y[i]*(1 - xx[i]);
    }

    std::array<Vector, 2> D{xx, yy};

    return D;
}

std::vector<double> duffyWeights(const std::vector<double>& nodes, const std::vector<double>& weights)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    std::array<Matrix, 2> V = meshgrid(nodes, nodes);
    Vector xx = ravel(V[0]);

    std::array<Matrix, 2> W = meshgrid(weights, weights);
    Vector w1 = ravel(W[0]);
    Vector w2 = ravel(W[1]);
    Vector w(w1.size());

    for(std::size_t i=0; i<xx.size(); i++)
    {
        w[i] = w1[i]*w2[i]*(1 - xx[i]);
    }

    return w;
}