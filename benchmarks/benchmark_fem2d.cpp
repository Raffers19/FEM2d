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

int main()
{
    using clock = std::chrono::steady_clock;
    using clocktype = std::chrono::duration<double>;
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Solver solver{};

    double minx = -1;
    double maxx = 1;
    double miny = -1;
    double maxy = 1;
    int Nx = 11;
    int Ny = 11;

    //Mesher benchmark//

    auto meshclockstart = clock::now();

    for(int i=0; i<1000; i++)
    {
    Mesher mesh(Nx, Ny, minx, miny, maxx, maxy);
    }

    auto meshclockend = clock::now();

    clocktype meshTime = meshclockend - meshclockstart;
}   