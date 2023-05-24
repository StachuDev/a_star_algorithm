#include <iostream>
#include <fstream>
#include <string>
#include "grid.h"
using namespace std;

// IMPLEMENTACJA OPERACJI NA 'GRIDZIE'

// -------------------------------------------------//
// CONSTRUCTORS
// -------------------------------------------------//
void Grid::generate_from_file(string filepath)
{
    string myText;
    ifstream MyReadFile(filepath);
    int row_iter = 0;
    while (getline(MyReadFile, myText))
    {
        int del_space_iterator = 0;
        for (int col_iter = 0; col_iter < colCount && del_space_iterator < colCount * 2 - 1; col_iter++)
        {
            grid[row_iter][col_iter] = myText[del_space_iterator] - 48;
            // przechodzimy po co drugim elemencie myText(zeby usnac spacjie)
            del_space_iterator += 2;
        }
        row_iter++;
    }
}

// -------------------------------------------------//
// GETTERS
// -------------------------------------------------//
int Grid::get_record(record perimeters)
{
    return grid[perimeters.wsp_x][perimeters.wsp_y];
};

double Grid::get_record_double(record perimeters)
{
    return grid_double[perimeters.wsp_x][perimeters.wsp_y];
};

record Grid::get_size()
{
    record size = {rowCount, colCount};
    return size;
};

//
// -------------------------------------------------//
// SETTERS
// -------------------------------------------------//

void Grid::set_record(record perimeters, int value)
{
    grid[perimeters.wsp_x][perimeters.wsp_y] = value;
};

void Grid::set_record_double(record perimeters, double value)
{
    grid_double[perimeters.wsp_x][perimeters.wsp_y] = value;
};

void Grid::set_size(int height, int width)
{
    rowCount = height;
    colCount = width;
    generate_grid();
};

// -------------------------------------------------//
// OTHER
// -------------------------------------------------//
void Grid::destroy()
{
    for (int i = 0; i < rowCount; ++i)
        free(grid[i]);
    free(grid);
}

void Grid::show()
{
    for (int j = 0; j < rowCount; j++)
    {
        for (int i = 0; i < colCount; i++)
        {
            cout << grid[j][i] << " ";
        }
        cout << endl;
    }
}
