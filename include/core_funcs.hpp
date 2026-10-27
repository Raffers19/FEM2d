#pragma once
#include <vector>
#include <array>
#include <utility>

inline std::vector<double> linspace(const double min, const double max, const int nodes)
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

inline std::array<std::vector<std::vector<double>>, 2> meshgrid(const std::vector<double>& x, const std::vector<double>& y)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    const int xsize = static_cast<int>(x.size());
    const int ysize = static_cast<int>(y.size());

    Matrix X(ysize, Vector(xsize));
    Matrix Y(ysize, Vector(xsize));

    for (int i = 0; i < ysize; i++)
    {
        X[i] = x;
    }

    for (int i = 0; i < ysize; i++)
    {
        for (int j = 0; j < xsize; j++)
        {
            Y[i][j] = y[i];
        }
    }

    return {std::move(X), std::move(Y)};
}

