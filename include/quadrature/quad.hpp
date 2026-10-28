#pragma once
#include <vector>
#include <array>

class Quadrature
{
private:
    std::array<std::vector<double>, 2> nodes;
    std::array<std::vector<int>, 3> con;
    int order;
    std::array<std::vector<double>, 2> refNodes;
    std::vector<double> refWeights;
    //std::vector<std::array<std::vector<double>, 2>> affNodes;
    //std::vector<std::vector<double>> affWeights;


public:
    Quadrature(const std::array<std::vector<double>, 2>& nodal_array, const std::array<std::vector<int>, 3>& connectivity, int quadOrder);
};


