#include <iostream>
#include <vector>
#include <array>
#include "core_funcs.hpp"
#include "mesh/mesh_funcs.hpp"
#include "print.hpp"

int main()
{
    
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    double startx = -1.0;
    double endx = 1.0;
    int Nx = 3;
    double starty = -1.0;
    double endy = 1.0;
    int Ny = 3;

    Vector x = linspace(startx, endx, Nx);
    Vector y = linspace(starty, endy, Ny);

    std::array<Matrix, 2> V = meshgrid(x, y);
    std::array<Vector, 2> nodes = gridToNode(V);

    //print(nodes[0]);
    //print(nodes[1]);
    print(V[0]);
    print(V[1]);



    

    return 0;
}