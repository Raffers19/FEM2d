#pragma once
#include <vector>
#include <array>


std::array<std::vector<double>, 2> gridToNode(const std::array<std::vector<std::vector<double>>, 2>& V);
std::array<std::vector<int>, 3> constructConnectivity(const int Nx, const int Ny);