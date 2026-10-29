#pragma once
#include <vector>
#include <array>

class Quadrature
{
private:
    int order;
    std::array<std::vector<double>, 2> refNodes;
    std::vector<double> refWeights;
    //std::vector<std::array<std::vector<double>, 2>> affNodes;
    //std::vector<std::vector<double>> affWeights;


public:
    Quadrature(int quadOrder);
    std::vector<std::vector<double>> getLocalStiff(double x1,double x2,double x3,double y1,double y2,double y3, int p) const;
};


