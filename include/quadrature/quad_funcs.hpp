#pragma once
#include <vector>


double legpoly(int n, double t);
std::vector<double> legaussNodes(int n);
std::vector<double> legaussWeights(const std::vector<double>& nodes);
std::array<std::vector<double>, 2> duffyNodes(const std::vector<double>& nodes);
std::vector<double> duffyWeights(const std::vector<double>& nodes, const std::vector<double>& weights);