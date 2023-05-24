#ifndef CHARACTER_H
#define CHARACTER_H
#include <list>
#include <string>
#include "grid.h"
using namespace std;




class AStarAlgorithm
{
public:
    record start_record;
    record end_record;

    int map_width;
    int map_height;

    list<record> closed_list;
    list<record> opened_list;

    // Grid closed_array;
    // Grid opened_array;
    // Grid parent_array;
    // Grid heuristic_array;

    record find_remove_lowest_heuristic();

    // fill all grids and return record to move (with the smallest heristic)

    void init_parent_array()
    {
        for (int row_iter = 0; row_iter < map_height; row_iter++)
        {
            for (int col_iter = 0; col_iter < map_width; col_iter++)
            {
                parent_array.grid[col_iter][row_iter] = 4;
            }
        }
    }

    void init_heuristic_array()
    {
        for (int row_iter = 0; row_iter < map_height; row_iter++)
        {
            for (int col_iter = 0; col_iter < map_width; col_iter++)
            {
                parent_array.grid_double[col_iter][row_iter] = -2;
            }
        }
    }

    // public:
    Grid map;
    Grid trace_grid;
    Grid parent_array;
    Grid heuristic_array;

    AStarAlgorithm();

    AStarAlgorithm(record start, record end, Grid map);

    void next_move();

    double calculate_heuristic(record selected);

    void generate_trace();

    void show_trace();

    // void set_map(Grid map);

    // void get_map(Grid map);
};
#endif
