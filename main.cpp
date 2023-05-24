#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
// #include <list>
#include "grid.h"
#include "a_star.h"

using namespace std;
int main()
{
    Grid grid(20, 20);
    grid.generate_from_file("tpoint.txt");
    // grid.show();

    grid.show();
    // record start = {0, 0};
    // record meta = {19, 1};

    // AStarAlgorithm astar(start, meta, grid);

    // astar.next_move();

    // astar.parent_array.show();
}
