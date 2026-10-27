#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

void print(int x)
{
    std::cout << x << '\n';
}

void print(double x)
{
    std::cout  << x << '\n';
}

void print(const std::vector<double>& x)
{
    const int xsize = static_cast<int>(x.size());

    for (int i = 0; i < xsize; i++)
    {
        //std::cout << x[i] << " ";
        //std::cout << std::setw(8) << x[i];
        std::cout << std::fixed
                  << std::setprecision(2)
                  << std::setw(8)
                  << x[i];
    }

    std::cout << '\n';
}

void print(const std::vector<int>& x)
{
    const int xsize = static_cast<int>(x.size());

    for (int i = 0; i < xsize; i++)
    {
        //std::cout << x[i] << " ";
        //std::cout << std::setw(8) << x[i];
        std::cout << std::fixed
                  << std::setprecision(2)
                  << std::setw(8)
                  << x[i];
    }

    std::cout << '\n';
}

void print(const std::vector<std::vector<double>>& X)
{
    const int rows = static_cast<int>(X.size());

    for (int j = 0; j < rows; j++)
    {
        print(X[j]);
    }

    std::cout << '\n';
}