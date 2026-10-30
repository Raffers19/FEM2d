#pragma once
#include <vector>
#include <array>
#include "core_funcs.hpp"
#include <cmath>


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

std::vector<std::vector<double>> computeLocalMass(const int p, const std::array<std::vector<double>, 2>& refnodes, const std::vector<double>& refweights, 
    const double x1, const double x2, const double x3, const double y1, const double y2, const double y3);

template<typename Func>
std::vector<double> computeLocalSource(Func func, const int p, const std::array<std::vector<double>, 2>& refnodes, const std::vector<double>& refweights, 
    const double x1, const double x2, const double x3, const double y1, const double y2, const double y3)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Matrix B = transformMatrix(x1, x2, x3, y1, y2, y3);
    std::array<Vector, 2> affnodes = affineNodes(refnodes, B, x3, y3);
    double det = std::abs(determinant(B));

    Matrix phi = lagrangeBasisFuncs(refnodes[0], refnodes[1], p);

    int n2 = static_cast<int>(affnodes[0].size());
    int b = static_cast<int>(phi.size());

    double f;
    Vector l(b);
    Vector presum(n2);

    for(int i=0; i<b; i++)
    {
        
        for(int j=0; j<n2; j++)
        {
            f = func(affnodes[0][j], affnodes[1][j]);
            presum[j] = f*phi[i][j]*refweights[j]*det;
        }

        l[i] = sum(presum);

    }

    return l;

}