#pragma once
#include <vector>
#include <array>

#include "quadrature/quad_funcs.hpp"

class Quadrature
{
private:
    int order;
    std::array<std::vector<double>, 2> refNodes;
    std::vector<double> refWeights;

public:
    Quadrature(int quadOrder);
    std::vector<std::vector<double>> getLocalStiff(double x1,double x2,double x3,double y1,double y2,double y3, int p) const;

    template<typename Func>
    std::vector<double> getLocalSource(Func func, double x1,double x2,double x3,double y1,double y2,double y3, int p) const;


};

template<typename Func>
std::vector<double> Quadrature::getLocalSource(Func func, double x1,double x2,double x3,double y1,double y2,double y3, int p) const
{
    std::vector<double> l = computeLocalSource(func, p, refNodes, refWeights, x1, x2, x3, y1, y2, y3);
    return l;
}
