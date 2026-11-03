#include <iostream>
#include <vector>
#include <array>
//#include "print.hpp"
#include <numbers>
#include <cmath>
#include "mesh/mesher.hpp"
#include "assembley/assembler.hpp"
#include "solvers/solver.hpp"
#include "core_funcs.hpp"

double efunc(double x, double y)
{
    const double pi = std::numbers::pi;

    return std::sin(pi * x) * std::sin(pi * y);
}

double func(double x, double y)
{
    const double pi = std::numbers::pi;

    return 2.0 * pi * pi
         * std::sin(pi * x)
         * std::sin(pi * y);
}

int main()
{
    
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    double minx = -1;
    double maxx = 1;
    double miny = -1;
    double maxy = 1;
    
    std::vector<double> N{9, 17, 21, 33};

    int Nt = static_cast<int>(N.size());
    Vector error(Nt);

    for(int n=0; n<Nt; n++)
    {
        int Nn = static_cast<int>(N[n]);
        
        //MESH CONSTRUCTION//
        Mesher mesh(Nn, Nn, minx, miny, maxx, maxy);

        std::array<std::vector<double>, 2> nodes = mesh.getNodes();
        std::array<std::vector<int>, 3> con = mesh.getConnectivity();
        std::vector<int> bc = mesh.getBoundary();

        //ASSEMBLER//
        Assembler assembler(nodes, con);

        Matrix A = assembler.poissonStiffnessP1();
        A = assembler.boundaryDirichletH(A, bc);

        Matrix M = assembler.massP1();

        Vector F = assembler.poissonSourceP1(func);
        F = assembler.boundaryDirichletH(F, bc);

        Vector Fe = assembler.poissonSourceP1(efunc);

        //SOLVER//
        Solver solver{};

        Vector U = solver.conjugateGradient(A, F);
        Vector Ue = solver.conjugateGradient(M, Fe);

        Vector Udif = minusVec(U, Ue);
        Vector MUdif = matmul(M, Udif);

        error[n] = std::sqrt(dot(Udif, MUdif));

        std::cout << "N = " << N[n]
          << ", Error = " << error[n]
          << '\n';

    }

    Vector h(Nt);

    for (int n = 0; n < Nt; ++n)
    {
        h[n] = (maxx - minx) / (N[n] - 1.0);
    }

    double grad = linearRegression(logVec(h), logVec(error));

    if (grad < 1.9 || grad > 2.1)
    {
        std::cout << "Poisson convergence test failed: "
                << grad << '\n';

        return 1;
    }

    std::cout << "Poisson convergence test passed: "
            << grad << '\n';

    return 0;
}