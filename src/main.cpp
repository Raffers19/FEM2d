#include <iostream>
#include <vector>
#include <array>
#include "print.hpp"
#include "mesh/mesher.hpp"

int main()
{
    
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    int Nx = 5;
    int Ny = 5;
    double minx = -1;
    double maxx = 1;
    double miny = -1;
    double maxy = 1;

    Mesher mesh(Nx, Ny, minx, miny, maxx, maxy);

    std::array<std::vector<double>, 2> nodes = mesh.getNodes();

    print(nodes[0]);
    print(nodes[1]);

    std::array<std::vector<int>, 3> con = mesh.getConnectivity();

    print(con[0]);
    print(con[1]);
    print(con[2]);

    return 0;
}