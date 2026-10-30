#pragma once

#include <vector>

std::vector<double> cgSolver(const std::vector<std::vector<double>>& A, const std::vector<double>& F, double tol = 1e-10, int maxIter = 10000);