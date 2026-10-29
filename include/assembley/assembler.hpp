#pragma once
#include <vector>
#include <array>


class Assembler
{
private:
    std::array<std::vector<double>, 2> nodes;
    std::array<std::vector<int>, 3> con;
    
public:
    Assembler(const std::array<std::vector<double>, 2> nodalArray, std::array<std::vector<int>, 3> connectivityArray);

    std::vector<std::vector<double>> poissonStiffness1d();

    //std::vector<double> poissonSource();
    
};


