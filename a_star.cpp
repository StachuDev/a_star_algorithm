#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <string>
#include "a_star.h"
using namespace std;



// ----------------------------------------------------
// IMPLEMENTACJA ALGORYTMU
// ----------------------------------------------------

void showlist(list<int> g)
{
    list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

// ----------------------------------------------------
// INICJALIZACJA SRODOWISKA
//  ----------------------------------------------------
AStarAlgorithm::AStarAlgorithm(record start, record end, Grid map)
{
    // inicjalizacja punktow startu i celu
    start_record = start;
    end_record = end;

    // inicjalizacja wymiarów naszej mapy
    record map_size = map.get_size();
    map_width = map_size.wsp_x;
    map_height = map_size.wsp_y;

    // inicjalizacja mapy
    map = map;

    // inicjalizacja wymiarow tablicy rodzicow
    parent_array.set_size(map_width, map_height);
    // wypełniamy czworkami
    init_parent_array();

    // inicjalizacja wymiarow tablicy heurystyki
    heuristic_array.set_size(map_width, map_height);
    // wypełniamy '-2'
    init_heuristic_array();
};

double AStarAlgorithm::calculate_heuristic(record selected)
{
    double odleglosc_start_selected = sqrt(pow(selected.wsp_x - start_record.wsp_x, 2) + pow(selected.wsp_y - start_record.wsp_y, 2));
    double odleglosc_selected_cel = sqrt(pow(end_record.wsp_x - selected.wsp_x, 2) + pow(end_record.wsp_y - selected.wsp_y, 2));
    double wynik = odleglosc_start_selected + odleglosc_selected_cel;

    return wynik;
}

// funkcja znajduje record wskazujący na najmniejszą wartosc heurystyki
// usuwa go z listy i zwraca jego wartosc
record AStarAlgorithm::find_remove_lowest_heuristic()
{
    list<record>::iterator list_iter, lowest_position;
    list_iter = opened_list.begin();

    // pobieramy wartość z iteratora
    record lowest = *list_iter;

    if (opened_list.size() == 1){
        opened_list.pop_back();
        return lowest;
    }

    double lowest_heuristic = heuristic_array.get_record_double(lowest);
    list_iter++;

    for (list_iter; list_iter != opened_list.end(); list_iter++)
    {
        if (heuristic_array.get_record_double(*list_iter) <= lowest_heuristic)
        {
            lowest = *list_iter;
            lowest_position = list_iter;
        }
    }
    opened_list.erase(lowest_position);

    return lowest;
};

void AStarAlgorithm::generate_trace(){
    record current = end_record;
    trace_grid = map;

    while(current.wsp_x != end_record.wsp_x or current.wsp_y != end_record.wsp_y){
        record move_array[4] =
            {{current.wsp_x + 1, current.wsp_y}, {current.wsp_x, current.wsp_y - 1}, {current.wsp_x - 1, current.wsp_y}, {current.wsp_x, current.wsp_y + 1}};
        trace_grid.set_record(current, 1);
        int move_direction = parent_array.get_record(current);
        current = move_array[move_direction];
    }
};

//===============================================
//       0         1        2
// 0:          [x-1, y]
// 1: [x, y-1] [x,   y] [x, y+1]
// 2:          [x+1, y]
//
// move order: down=0, left=1, up=2, right=3
//================================================


// fill all grids and return record to move (with the smallest heristic)
void AStarAlgorithm::next_move()
{
    record current = start_record;
    while (current.wsp_x != start_record.wsp_x and current.wsp_y != current.wsp_y)
    {
        closed_list.push_back(current);
        // kolejno recordy: down, left, up, right
        record move_array[4] =
            {{current.wsp_x + 1, current.wsp_y}, {current.wsp_x, current.wsp_y - 1}, {current.wsp_x - 1, current.wsp_y}, {current.wsp_x, current.wsp_y + 1}};

        // Filling next positions in ours containers (parent_array and heuristic_array)
        // DOWN
        if (current.wsp_x + 1 < map_height && map.get_record(move_array[0]) != 5)
        {
            // select 'down' position in opened_array
            // opened_array[current.wsp_x + 1][current.wsp_y] = 1;
            opened_list.push_back(move_array[0]);

            if (heuristic_array.get_record_double(move_array[0]) != -2)
            {
                // select parent position as '2' (up)
                parent_array.set_record(move_array[0], 2);

                // select heurystyka in heurestyka_array
                double value = calculate_heuristic(move_array[0]);
                heuristic_array.set_record_double(move_array[0], value);
            }
            else
            {
                // sprawdzamy czy nowa heurystyka jest mniejsza od starej
                double value = calculate_heuristic(move_array[0]);
                if (value < heuristic_array.get_record_double(move_array[0]))
                {
                    heuristic_array.set_record_double(move_array[0], value);

                    parent_array.set_record(move_array[0], 2);
                }
                // jezeli bedzie wieksza / rowana to nic nie zamieniamy
            }
        }

        // LEFT
        if (current.wsp_y - 1 > 0 && map.get_record(move_array[1]) != 5)
        {
            opened_list.push_back(move_array[1]);

            if (heuristic_array.get_record_double(move_array[1]) != -2)
            {
                parent_array.set_record(move_array[1], 3);
                double value = calculate_heuristic(move_array[1]);
                heuristic_array.set_record_double(move_array[1], value);
            }
            else
            {
                // sprawdzamy czy nowa heurystyka jest mniejsza od starej
                double value = calculate_heuristic(move_array[1]);
                if (value < heuristic_array.get_record_double(move_array[1]))
                {
                    heuristic_array.set_record_double(move_array[1], value);
                    parent_array.set_record(move_array[1], 3);
                }
                // jezeli bedzie wieksza / rowana to nic nie zamieniamy
            }
        }

        // UP
        if (current.wsp_x - 1 > 0 && map.get_record(move_array[2]) != 5)
        {
            // selected = {current.wsp_x - 1, current.wsp_y};
            // opened_array[current.wsp_x - 1][current.wsp_y] = 1;
            opened_list.push_back(move_array[2]);

            // sprawdzamy czy heurystyka nie jest jeszcze ustawiona
            if (heuristic_array.get_record_double(move_array[2]) != -2)
            {
                parent_array.set_record(move_array[2], 0);

                double value = calculate_heuristic(move_array[2]);
                heuristic_array.set_record_double(move_array[2], value);
            } // gdy już istnije
            else
            {
                // sprawdzamy czy nowa heurystyka jest mniejsza od starej
                double value = calculate_heuristic(move_array[2]);
                if (value < heuristic_array.get_record_double(move_array[2]))
                {
                    heuristic_array.set_record_double(move_array[2], value);

                    parent_array.set_record(move_array[2], 0);
                }
                // jezeli bedzie wieksza / rowana to nic nie zamieniamy
            }
        }

        // RIGHT
        if (current.wsp_y + 1 < map_width && map.get_record(move_array[3]) != 5)
        {
            // selected = {current.wsp_x, current.wsp_y + 1};
            // opened_array[current.wsp_x][current.wsp_y + 1] = 1;
            opened_list.push_back(move_array[3]);

            if (heuristic_array.get_record_double(move_array[3]) != -2)
            {
                parent_array.set_record(move_array[3], 1);

                double value = calculate_heuristic(move_array[3]);
                heuristic_array.set_record_double(move_array[3], value);
            }
            else
            {
                // sprawdzamy czy nowa heurystyka jest mniejsza od starej
                double value = calculate_heuristic(move_array[3]);
                if (value < heuristic_array.get_record_double(move_array[3]))
                {
                    heuristic_array.set_record_double(move_array[3], value);

                    parent_array.set_record(move_array[3], 1);
                }
                // jezeli bedzie wieksza / rowana to nic nie zamieniamy
            }
        }

        // gdy po sprawdzeniu kieruwnow lista otwarta pozostaje pusta
        // konczymy wykonywanie algorytmu
        if (opened_list.empty())
            break;

        current = find_remove_lowest_heuristic();
    }

    // Gry dotarliśmy do celu przechodzimy po rodzicach do startu
    generate_trace();
};

void AStarAlgorithm::show_trace(){
    trace_grid.show();
};
