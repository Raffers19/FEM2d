#include <iostream>
#include <cmath>
#include <vector>
#include "solvers/solver.hpp"

int main()
{
    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    Matrix A(2, Vector(2));

    A[0][0] = 4.0;
    A[0][1] = 1.0;
    A[1][0] = 1.0;
    A[1][1] = 3.0;

    Vector F(2);
    
    F[0] = 1.0;
    F[1] = 2.0;

    Solver solver{};

    Vector u = solver.conjugateGradient(A, F);

    double tol = 1e-12;
    if (std::abs(u[0] - 1.0/11.0)<tol && std::abs(u[1] - 7.0/11.0)<tol)
    {
        std::cout << "CG solver test successful\n";
        return 0;
    }else{
        std::cout << "CG solver test unsuccessful\n";
        return 1;
    }

}