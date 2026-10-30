#pragma once
#include <vector>

class Solver
{
private:
    /* data */
public:
    Solver();
    
    std::vector<double> conjugateGradient(const std::vector<std::vector<double>>& A, const std::vector<double>& b);

};


