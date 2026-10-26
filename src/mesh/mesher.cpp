#include "vec2d.hpp"
#include "mesh/mesh_funcs.hpp"
#include <vector>

struct connect
{
    int a;
    int b;
    int c;
};

class Mesher
{
private:
    int Nx;
    int Ny;
    double minx;
    double miny;
    double maxx;
    double maxy;
public:
    Mesher(int xnodes, int ynodes, double lower_x_limit, double lower_y_limit, double upper_x_limit, double upper_y_limit)
        : Nx{xnodes}, Ny{ynodes}, minx{lower_x_limit}, miny{lower_y_limit}, maxx{upper_x_limit}, maxy{upper_y_limit}
    {

    }
    
};


/*mesher::mesher()
{
}

mesher::~mesher()
{
}*/
