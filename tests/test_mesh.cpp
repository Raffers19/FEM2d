#include "mesh/mesher.hpp"
#include "mesh/mesh_funcs.hpp"
#include "core_funcs.hpp"


#include <array>
#include <cmath>
#include <iostream>
#include <vector>


int main()
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    double minx = -1;
    double maxx = 1;
    double miny = -1;
    double maxy = 1;

    double tol = 1e-12;

    for(int i=2; i<10; i++)
    {
        for(int j=2; j<10; j++)
        {
            Mesher mesh(i, j, minx, miny, maxx, maxy);
            std::array<std::vector<double>, 2> nodes = mesh.getNodes();
            std::array<std::vector<int>, 3> con = mesh.getConnectivity();
            int tt = static_cast<int>(con[0].size());

            int expectedTriangles = 2*(i-1)*(j-1);

            if (tt != expectedTriangles)
            {
                std::cout << "Incorrect triangle count\n";
                return 1;
            }
            
            double s = 0;
            

            for(int k=0; k<tt; k++)
            {
                s += triArea(nodes[0][con[0][k]],nodes[0][con[1][k]],nodes[0][con[2][k]],nodes[1][con[0][k]],nodes[1][con[1][k]],nodes[1][con[2][k]]);
            }

            if(std::abs(s-4)>tol)
            {
                std::cout << "Incorrect area\n";
                return 1;
            }

        }
    }

    std::cout << "Tests passed successfully\n";
    return 0;
}