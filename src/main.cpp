#include <iostream>
#include <vector>
#include <array>
#include "print.hpp"
#include "mesh/mesher.hpp"
#include "assembley/assembler.hpp"

double func(const double x, const double y)
{
    return x*x + y*y - 0.4*0.4;
}

int main()
{
    
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    int Nx = 3;
    int Ny = 3;
    double minx = -1;
    double maxx = 1;
    double miny = -1;
    double maxy = 1;
    //int order = 5;

    Mesher mesh(Nx, Ny, minx, miny, maxx, maxy);

    std::array<std::vector<double>, 2> nodes = mesh.getNodes();
    std::array<std::vector<int>, 3> con = mesh.getConnectivity();
    std::vector<int> bc = mesh.getBoundary();

    Assembler assembler(nodes, con);

    Matrix A = assembler.poissonStiffnessP1();
    A = assembler.boundaryDirichletH(A, bc);

    Vector F = assembler.poissonSourceP1(func);
    F = assembler.boundaryDirichletH(F, bc);

    print(A);
    print(F);



    return 0;
}