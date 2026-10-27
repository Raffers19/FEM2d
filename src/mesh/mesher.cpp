//#include "vec2d.hpp"
#include "mesh/mesher.hpp"
#include "mesh/mesh_funcs.hpp"
#include "core_funcs.hpp"
#include <vector>
#include <array>

Mesher::Mesher(int xnodes, int ynodes, double lower_x_limit, double lower_y_limit, double upper_x_limit, double upper_y_limit)
    : Nx{xnodes}, Ny{ynodes}, minx{lower_x_limit}, miny{lower_y_limit}, maxx{upper_x_limit}, maxy{upper_y_limit}
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;


    Vector x = linspace(minx, maxx, Nx);
    Vector y = linspace(miny, maxy, Ny);

    std::array<Matrix, 2> V = meshgrid(x, y);
    nodes = gridToNode(V);
    con = constructConnectivity(Nx, Ny);

}

std::array<std::vector<double>, 2> Mesher::getNodes() const
{
    return nodes;
}

std::array<std::vector<int>, 3> Mesher::getConnectivity() const 
{
    return con;
}
    
