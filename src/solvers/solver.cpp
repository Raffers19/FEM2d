#include "solvers/solver.hpp"
#include "solvers/solver_funcs.hpp"
#include <vector>

Solver::Solver()
{
}

std::vector<double> Solver::conjugateGradient(const std::vector<std::vector<double>>& A, const std::vector<double>& b)
{
    std::vector<double> U = cgSolver(A, b);
    return U;
}