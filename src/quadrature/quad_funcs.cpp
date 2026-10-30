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

std::vector<std::vector<double>> transformMatrix(const double x1, const double x2, const double x3, const double y1, const double y2, const double y3)
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

std::array<std::vector<double>, 2> affineNodes(const std::array<std::vector<double>, 2>& refnodes, const std::vector<std::vector<double>>& B, const double x3, const double y3)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Matrix x(2, Vector(refnodes[0].size()));
    x[0] = refnodes[0];
    x[1] = refnodes[1];

    Matrix aff = matmul(B, x);

    for(int j=0; j<refnodes[0].size(); j++)
    {
        aff[0][j] += x3;
        aff[1][j] += y3;
    }
    
    std::array<std::vector<double>, 2> affnodes{aff[0], aff[1]};

    return affnodes;
}

std::vector<std::vector<double>> lagrangeBasisFuncs(const std::vector<double>& x, const std::vector<double>& y, int p)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const std::size_t Nq = x.size();
    const std::size_t Np = (static_cast<std::size_t>(p) + 1) * (p + 2) / 2;

    Matrix L(Np, Vector(Nq, 0.0));

    // Evaluate the barycentric Lagrange polynomials
    std::size_t row = 0;

    for (int i = 0; i <= p; i++)
    {
        for (int j = 0; j <= p - i; j++)
        {
            const int k = p - i - j;

            for (std::size_t q = 0; q < Nq; q++)
            {
                const double lambda1 = 1.0 - x[q] - y[q];
                const double lambda2 = x[q];
                const double lambda3 = y[q];

                double value = 1.0;

                for (int a = 0; a < i; a++)
                {
                    value *= (p * lambda1 - a) / (a + 1);
                }

                for (int b = 0; b < j; b++)
                {
                    value *= (p * lambda2 - b) / (b + 1);
                }

                for (int c = 0; c < k; c++)
                {
                    value *= (p * lambda3 - c) / (c + 1);
                }

                L[row][q] = value;
            }

            row++;
        }
    }

    return L;
}

std::vector<std::vector<std::vector<double>>> lagrangeGradientFuncs(const std::vector<double>& x, const std::vector<double>& y, int p)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;
    using Tensor = std::vector<Matrix>;

    if (p < 0)
    {
        throw std::invalid_argument(
            "Polynomial degree must be nonnegative"
        );
    }

    if (x.size() != y.size())
    {
        throw std::invalid_argument(
            "x and y must have the same size"
        );
    }

    const std::size_t Nq = x.size();
    const std::size_t Np =
        (static_cast<std::size_t>(p) + 1) * (p + 2) / 2;

    Tensor grad(Np, Matrix(2, Vector(Nq, 0.0)));

    // Evaluate a 1D barycentric polynomial factor
    // and its derivative.
    auto factor = [p](double lambda, int degree)
        -> std::array<double, 2>
    {
        double value = 1.0;
        double derivative = 0.0;

        for (int a = 0; a < degree; a++)
        {
            const double f =
                (p * lambda - a) / (a + 1);

            const double df =
                static_cast<double>(p) / (a + 1);

            // Product rule
            derivative = derivative*f + value*df;
            value *= f;
        }

        return {value, derivative};
    };

    std::size_t row = 0;

    for (int i = 0; i <= p; i++)
    {
        for (int j = 0; j <= p - i; j++)
        {
            const int k = p - i - j;

            for (std::size_t q = 0; q < Nq; q++)
            {
                const double lambda1 = 1.0 - x[q] - y[q];
                const double lambda2 = x[q];
                const double lambda3 = y[q];

                const auto F1 = factor(lambda1, i);
                const auto F2 = factor(lambda2, j);
                const auto F3 = factor(lambda3, k);

                const double dLdlambda1 =
                    F1[1] * F2[0] * F3[0];

                const double dLdlambda2 =
                    F1[0] * F2[1] * F3[0];

                const double dLdlambda3 =
                    F1[0] * F2[0] * F3[1];

                // Chain rule
                grad[row][0][q] =
                    -dLdlambda1 + dLdlambda2;

                grad[row][1][q] =
                    -dLdlambda1 + dLdlambda3;
            }

            row++;
        }
    }

    return grad;
}

std::vector<std::vector<double>> computeLocalStiff(const int p, const std::array<std::vector<double>, 2>& refnodes, const std::vector<double>& refweights, 
    const double x1, const double x2, const double x3, const double y1, const double y2, const double y3)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Matrix B = transformMatrix(x1, x2, x3, y1, y2, y3);
    Matrix BT = transpose(B);
    double det = determinant(BT);
    Matrix invBT = inverse(BT);
    std::vector<std::vector<Vector>> dphi = lagrangeGradientFuncs(refnodes[0], refnodes[1], p);

    const std::size_t b = dphi.size();
    const std::size_t n2 = dphi[0][0].size();

    Matrix local(b, Vector(b));

    for(int i=0; i<b; i++)
    {
        for(int j=0; j<b; j++)
        {
            Matrix a = matmul(invBT, dphi[i]);
            Matrix b = matmul(invBT, dphi[j]);

            Vector u = dot(a, b);

            for(int k=0; k<u.size(); k++)
            {
                u[k] = u[k]*std::abs(det)*refweights[k];   
            }

            local[i][j] = sum(u);
        }

        
    }

    return local;

}

