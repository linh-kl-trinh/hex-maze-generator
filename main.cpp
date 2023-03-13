#include <iostream>

#include "DrawMaze.h"
using namespace std;

int main() {
    // Radius of the board
    int radius = 0;
    bool valid_input = false;
    while (!valid_input) {
        cout << "Choose a radius for the board: ";
        cin >> radius;

        if (cin.fail() || radius <= 0) {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid_input = true;
        }
    }

    // Max value of coordinates
    int max_coord = radius-1;
    
    // Create board
    HexBoard board(radius);

    // Size of hexagon for drawing
    int size = 20;

    // Starting coordinate of the maze
    int q = 0;
    int r = 0;
    valid_input = false;
    while (!valid_input) {
        cout << "Choose the q coordinate to start (from ";
        cout << -max_coord;
        cout << " to ";
        cout << max_coord;
        cout << "): ";
        cin >> q;

        if (cin.fail() || q < -max_coord || q > max_coord) {
            cout << "Invalid input. Please enter an integer in the specified range." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid_input = true;
        }
    }
    valid_input = false;
    while (!valid_input) {
        cout << "Choose the r coordinate to start (from "; 
        cout << max(-max_coord, -q-max_coord); 
        cout << " to "; 
        cout << min(max_coord, -q+max_coord);
        cout << "): ";
        cin >> r;

        if (cin.fail() || r < max(-max_coord, -q-max_coord) || r > min(max_coord, -q+max_coord)) {
            cout << "Invalid input. Please enter an integer in the specified range." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid_input = true;
        }
    }
    
    board.generate_maze({q, r}, 0.5);

    PNG output = DrawMaze::draw_maze(board, size, "none");
    output.writeToFile("maze.png");

    output = DrawMaze::draw_maze(board, size, "path");
    output.writeToFile("maze coloured based on path distance.png");

    board.solve_maze();

    output = DrawMaze::draw_solution(board, size, "none");
    output.writeToFile("maze with solutions.png");

    cout << board.longest_path_dist << endl;
    cout << board.solution.size() << endl;

    output = DrawMaze::draw_solution(board, size, "path");
    output.writeToFile("maze with solutions coloured based on path distance.png");
}
