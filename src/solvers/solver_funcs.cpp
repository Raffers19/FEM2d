#include "solvers/solver_funcs.hpp"
#include "core_funcs.hpp"
#include <vector>
#include <cmath>

std::vector<double> cgSolver(const std::vector<std::vector<double>>& A, const std::vector<double>& F, double tol, int maxIter)
{

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int n = static_cast<int>(F.size());

    Vector u(n, 0.0);
    Vector r = F;
    Vector p = r;

    double rsold = dot(r, r);
    double normF = std::sqrt(rsold);

    if (normF == 0.0)
        return u;

    for (int k = 0; k < maxIter; k++)
    {
        Vector Ap = matmul(A, p);

        double denom = dot(p, Ap);

        if (denom <= 0.0)
            throw std::runtime_error(
                "matrix may not be positive definite"
            );

        double alpha = rsold / denom;

        for (int i = 0; i < n; i++)
        {
            u[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        double rsnew = dot(r, r);

        if (std::sqrt(rsnew) / normF < tol)
            return u;

        double beta = rsnew / rsold;

        for (int i = 0; i < n; i++)
        {
            p[i] = r[i] + beta * p[i];
        }

        rsold = rsnew;
    }

    throw std::runtime_error(
        "Conjugate Gradient failed to converge"
    );
}