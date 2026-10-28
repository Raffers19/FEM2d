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
};


