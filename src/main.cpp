#include <iostream>
#include <vector>
#include <array>
#include "print.hpp"
#include "mesh/mesher.hpp"

#include "quadrature/quad_funcs.hpp"

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
    int order = 5;

    Mesher mesh(Nx, Ny, minx, miny, maxx, maxy);

    std::array<std::vector<double>, 2> nodes = mesh.getNodes();
    std::array<std::vector<int>, 3> con = mesh.getConnectivity();

    std::vector<double> legnodes = legaussNodes(order);
    std::vector<double> legweights = legaussWeights(legnodes);

    print(legnodes);
    print(legweights);


    return 0;
}