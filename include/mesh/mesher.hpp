#pragma once
#include <vector>
#include <array>



class Mesher
{
private:
    int Nx;
    int Ny;
    double minx;
    double miny;
    double maxx;
    double maxy;
    std::array<std::vector<double>, 2> nodes;
    std::array<std::vector<int>, 3> con;
    std::vector<int> bc;

public:
    Mesher(int xnodes, int ynodes, double lower_x_limit, double lower_y_limit, double upper_x_limit, double upper_y_limit);

    std::array<std::vector<double>, 2> getNodes() const;

    std::array<std::vector<int>, 3> getConnectivity() const;

    std::vector<int> getBoundary() const;
    
};


/*mesher::mesher()
{
}

mesher::~mesher()
{
}*/
