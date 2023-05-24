#ifndef CHARACTERS_H
#define CHARACTERS_H
using namespace std;
struct record
{
    int wsp_x;
    int wsp_y;
};


class Grid
{
public:
    int rowCount;
    int colCount;
    // zakładam że zmienne rowCount, colCount są już ustawione
    void generate_grid()
    {
        grid = new int *[rowCount];
        for (int i = 0; i < rowCount; ++i)
            grid[i] = new int[colCount];
    }

    // public:
    int **grid;
    double **grid_double;
    // konstruktor
    Grid();

    Grid(int height, int width)
    {
        rowCount = height;
        colCount = width;
        generate_grid();

        // grid = new int *[height];
        // for (int i = 0; i < height; ++i)
        //     grid[i] = new int[width];
    };

    void generate_grid_double()
    {
        grid_double = new double *[rowCount];
        for (int i = 0; i < rowCount; ++i)
            grid_double[i] = new double[colCount];
    }

    void set_record_double(record perimeters, double value);

    void generate_from_file(string file_path);

    // poberanie rekordu z tabeli
    int get_record(record perimeters);

    double get_record_double(record perimeters);

    record get_size();

    // wczytywanie rekordu do tabeli
    void set_record(record perimeters, int value);

    void set_size(int height, int width);

    void destroy();

    void show();
};
#endif
