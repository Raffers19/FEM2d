#include <iostream>
#include <vector>
#include <array>
#include <numbers>
#include "print.hpp"
#include "mesh/mesher.hpp"
#include "assembley/assembler.hpp"
#include "solvers/solver.hpp"
#include "core_funcs.hpp"
#include <chrono>


double func(double x, double y)
{
    const double pi = std::numbers::pi;

    return 2.0 * pi * pi
         * std::sin(pi * x)
         * std::sin(pi * y);
}

std::chrono::duration<double> meshGenBench(int N, int trials)
{
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;

    auto meshclockstart = clock::now();
    //double checksum = 0.0;

    for(int i=0; i<trials; i++)
    {
    Mesher mesh(N, N, -1, -1, 1, 1);
    }

    auto meshclockend = clock::now();

    clocktype meshTime = meshclockend - meshclockstart;

    return meshTime/trials;

}

std::chrono::duration<double> stiffMatBenchP1(int N, int trials)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;

    Mesher mesh(N, N, -1, -1, 1, 1);
    std::array<std::vector<double>, 2> nodes = mesh.getNodes();
    std::array<std::vector<int>, 3> con = mesh.getConnectivity();
    std::vector<int> bc = mesh.getBoundary();

    Assembler assembler(nodes, con);
    double checksum = 0.0;

    auto clockstart = clock::now();

    for(int i=0; i<trials; i++)
    {
        Matrix A = assembler.poissonStiffnessP1();
        A = assembler.boundaryDirichletH(A, bc);
        checksum += A[0][0];
    }

    auto clockend = clock::now();
    clocktype time = clockend - clockstart;

    return time/trials;

}

std::chrono::duration<double> massMatBenchP1(int N, int trials)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;

    Mesher mesh(N, N, -1, -1, 1, 1);
    std::array<std::vector<double>, 2> nodes = mesh.getNodes();
    std::array<std::vector<int>, 3> con = mesh.getConnectivity();
    //std::vector<int> bc = mesh.getBoundary();

    Assembler assembler(nodes, con);
    double checksum = 0.0;

    auto clockstart = clock::now();

    for(int i=0; i<trials; i++)
    {
        Matrix M = assembler.massP1();
        checksum += M[0][0];
    }

    auto clockend = clock::now();
    clocktype time = clockend - clockstart;

    return time/trials;

}

std::chrono::duration<double> sourceVecBenchP1(int N, int trials)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;

    Mesher mesh(N, N, -1, -1, 1, 1);
    std::array<std::vector<double>, 2> nodes = mesh.getNodes();
    std::array<std::vector<int>, 3> con = mesh.getConnectivity();
    std::vector<int> bc = mesh.getBoundary();

    Assembler assembler(nodes, con);
    double checksum = 0.0;

    auto clockstart = clock::now();

    for(int i=0; i<trials; i++)
    {
        Vector F = assembler.poissonSourceP1(func);
        F = assembler.boundaryDirichletH(F, bc);
        checksum += F[0];
    }

    auto clockend = clock::now();
    clocktype time = clockend - clockstart;

    return time/trials;

}

std::chrono::duration<double> solverCGBench(int N, int trials)
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;

    Mesher mesh(N, N, -1, -1, 1, 1);
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

    //SOLVER//
    Solver solver{};
    double checksum = 0.0;

    auto clockstart = clock::now();

    for(int i=0; i<trials; i++)
    {
        Vector U = solver.conjugateGradient(A, F);
        checksum += U[0];
    }

    auto clockend = clock::now();
    clocktype time = clockend - clockstart;

    return time/trials;

}

int main()
{
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Solver solver{};

    //Mesher benchmark//
    clocktype meshTime5  = meshGenBench(5, 1000);
    clocktype meshTime11 = meshGenBench(11, 1000);
    clocktype meshTime31 = meshGenBench(31, 1000);
    clocktype meshTime73 = meshGenBench(73, 1000);

    std::cout << "Mesh Benchmark Complete\n";

    //Stiffness Benchmark
    clocktype stiffTime5P1  = stiffMatBenchP1(5, 20);
    clocktype stiffTime11P1 = stiffMatBenchP1(11, 20);
    clocktype stiffTime31P1 = stiffMatBenchP1(31, 20);
    clocktype stiffTime73P1 = stiffMatBenchP1(73, 20);

    std::cout << "Stiffness Benchmark Complete\n";

    //Mass Benchmark
    clocktype massTime5P1  = massMatBenchP1(5, 20);
    clocktype massTime11P1 = massMatBenchP1(11, 20);
    clocktype massTime31P1 = massMatBenchP1(31, 20);
    clocktype massTime73P1 = massMatBenchP1(73, 20);

    std::cout << "Mass Benchmark Complete\n";

    //Source Benchmark
    clocktype sourceTime5P1  = sourceVecBenchP1(5, 20);
    clocktype sourceTime11P1 = sourceVecBenchP1(11, 20);
    clocktype sourceTime31P1 = sourceVecBenchP1(31, 20);
    clocktype sourceTime73P1 = sourceVecBenchP1(73, 20);

    std::cout << "Source Benchmark Complete\n";

    //Solver Benchmark
    clocktype CGTime5  = solverCGBench(5, 10);
    clocktype CGTime11 = solverCGBench(11, 10);
    clocktype CGTime31 = solverCGBench(31, 10);
    clocktype CGTime73 = solverCGBench(73, 10);

    std::cout << "Solver Benchmark Complete\n\n";

    std::cout << "MESH BENCHMARK\n";
    std::cout << "32 Element mesh construction time:"<< meshTime5 << '\n';
    std::cout << "200 Element mesh construction time:"<< meshTime11 << '\n';
    std::cout << "1,800 Element mesh construction time:"<< meshTime31 << '\n';
    std::cout << "10,658 Element mesh construction time:"<< meshTime73 << '\n';
    
    std::cout << "STIFFNESS BENCHMARK\n";
    std::cout << "96 DoF Stiffness construction time:"<< stiffTime5P1 << '\n';
    std::cout << "600 DoF Stiffness construction time:"<< stiffTime11P1 << '\n';
    std::cout << "5,400 DoF Stiffness construction time:"<< stiffTime31P1 << '\n';
    std::cout << "31,974 DoF Stiffness construction time:"<< stiffTime73P1 << '\n';

    std::cout << "MASS BENCHMARK\n";
    std::cout << "96 DoF Mass construction time:"<< massTime5P1 << '\n';
    std::cout << "600 DoF Mass construction time:"<< massTime11P1 << '\n';
    std::cout << "5,400 DoF Mass construction time:"<< massTime31P1 << '\n';
    std::cout << "31,974 DoF Mass construction time:"<< massTime73P1 << '\n';

    std::cout << "SOURCE BENCHMARK\n";
    std::cout << "96 DoF Source construction time:"<< sourceTime5P1 << '\n';
    std::cout << "600 DoF Source construction time:"<< sourceTime11P1 << '\n';
    std::cout << "5,400 DoF Source construction time:"<< sourceTime31P1 << '\n';
    std::cout << "31,974 DoF Source construction time:"<< sourceTime73P1 << '\n';

    std::cout << "SOLVER BENCHMARK\n";
    std::cout << "96 DoF CG Solver time:"<< CGTime5 << '\n';
    std::cout << "600 DoF CG Solver time:"<< CGTime11 << '\n';
    std::cout << "5,400 DoF CG Solver time:"<< CGTime31 << '\n';
    std::cout << "31,974 DoF CG Solver time:"<< CGTime73 << '\n';

    return 0;
}   

