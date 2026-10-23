#pragma once
#include <vector>
#include <array>

std::vector<double> linspace(const double min, const double max, const int nodes)
{
    const double step = (max - min)/(nodes - 1);
    
    std::vector<double> space(nodes);
    space[0] = min;

    for(int i=1; i<nodes; i++)
    {
        space[i] = space[i - 1] + step;
    }

    return space;
}

std::array<std::vector<std::vector<double>>,2> meshgrid(const std::vector<double>& x, const std::vector<double>& y)
{
    const int xsize = static_cast<int>(x.size());
    const int ysize = static_cast<int>(y.size());

    std::vector<std::vector<double>> X(xsize, std::vector<double>(ysize));
    std::vector<std::vector<double>> Y(ysize, std::vector<double>(xsize));

    

}


