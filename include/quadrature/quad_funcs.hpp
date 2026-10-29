#pragma once
#include <vector>
#include <array>


double legpoly(int n, double t);
std::vector<double> legaussNodes(int n);
std::vector<double> legaussWeights(const std::vector<double>& nodes);
std::array<std::vector<double>, 2> duffyNodes(const std::vector<double>& nodes);
std::vector<double> duffyWeights(const std::vector<double>& nodes, const std::vector<double>& weights);
std::vector<std::vector<double>> transformMatrix(const double x1, const double x2, const double x3, const double y1, const double y2, const double y3);
std::array<std::vector<double>, 2> affineNodes(const std::array<std::vector<double>, 2>& refnodes, const std::vector<std::vector<double>>& B, double x3, double y3);
std::vector<std::vector<double>> lagrangeBasisFuncs(const std::vector<double>& x, const std::vector<double>& y, int p);
std::vector<std::vector<std::vector<double>>> lagrangeGradientFuncs(const std::vector<double>& x, const std::vector<double>& y, int p);
std::vector<std::vector<double>> computeLocalStiff(const int p, const std::array<std::vector<double>, 2>& refnodes, const std::vector<double>& refweights, 
    const double x1, const double x2, const double x3, const double y1, const double y2, const double y3);