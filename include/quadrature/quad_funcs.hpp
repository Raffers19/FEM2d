#pragma once
#include <vector>


double legpoly(int n, double t);
std::vector<double> legaussNodes(int n);
std::vector<double> legaussWeights(const std::vector<double>& nodes);