#include "HexBoard.h"

#include <iostream>

#include "stack.h"

HexBoard::HexBoard(int radius) {
    this->radius = radius;
    longest_path_dist = 0;
    start_coord = {0,0};
    end_coord = {0,0};
    create_board();
    configure_cells();
}

void HexBoard::create_board() {
    int size = radius-1;
    for (int q = -size; q <= size; q++) {
        for (int r = max(-size, -q-size); r <= min(size, -q+size); r++) {
            cells[make_pair(q, r)] = new HexCell(q,r);
        }
    }
}

void HexBoard::configure_cells() {
    for (auto cell_pair : cells) {
        auto cell_coord = cell_pair.first;
        auto cell = cell_pair.second;
    
        // Get neighbour coordinates for this cell
        auto neigh_coords = get_neigh_coords(cell_coord);
        
        // Set each neighbour for this cell
        for (auto neigh_coord : neigh_coords) {
            auto neigh_pair = cells.find(neigh_coord);
            if (neigh_pair != cells.end()) {
                HexCell *neigh_cell = neigh_pair->second;
                cell->neighbours[cell->get_neighbour_side(neigh_cell)] = neigh_cell;
            }
        }
    }
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    // Assign this->start_coord
    this->start_coord = start_coord;

    // Initialize visited map
    map<pair<int, int>, bool> visited;

    // Initialize the cell stack
    Stack<HexCell*> cellStack;

    // Add the start_coord to the stack and mark as visited
    cellStack.push(cells[start_coord]);
    visited[start_coord] = true;

    // Initialize longest path to edge
    int longest_path_to_edge = 0;

    // While stack is not empty
    while (!cellStack.isEmpty()) {
        // Peek the top of the stack
        HexCell *curr_cell = cellStack.peek();
        
        // Choose the neighbour to visit
        HexCell *neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);

        // If the neighbour exists
        if (neigh_cell != nullptr) {
            // Link curr_cell with neigh_cell
            curr_cell->link(neigh_cell);

            // Set neigh_coord to be visited
            pair<int, int> neigh_coord = {neigh_cell->q, neigh_cell->r};
            visited[neigh_coord] = true;

            // Update the neigh_cell's path distance
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + curr_cell->distance(neigh_cell);
            int curr_dist = neigh_cell->path_dist_from_start;
            
            // If necessary, update length of longest path to edge
            if (curr_dist > longest_path_to_edge && neigh_cell->is_edge()) {
                longest_path_to_edge = curr_dist;
                // Update the end coordinate
                end_coord = neigh_coord;    
            }

            // If necessary, update length of longest path so far (longest_path_dist)
            if (curr_dist > longest_path_dist) {
                longest_path_dist = curr_dist;    
            }

            // Push neigh_cell into the stack
            cellStack.push(neigh_cell);            
        } else {
            //Otherwise (if chooseNeighbour returns nullptr), pop the stack
            cellStack.pop();
        }
    }
}

void HexBoard::solve_maze() {
    // Start at the end coordinate and work backwards to the start
    HexCell* curr_cell = cells[end_coord];
    
    while (make_pair(curr_cell->q, curr_cell->r) != start_coord) {
        // Add current cell's coordinate to the solution vector
        solution.push_back({curr_cell->q, curr_cell->r});
        
        // Find the neighbour that comes immediately before curr_cell in the path
        HexCell* next_cell = nullptr;
        
        for (int i = 0; i <= 5; i++) {
            HexCell *n = curr_cell->links[i];
            if (n) {
                if (n->path_dist_from_start == curr_cell->path_dist_from_start-1) {
                    next_cell = n;
                }
            }
        }

        // Move to the next cell
        curr_cell = next_cell;
    }

    // Add the start coordinate to the solution vector
    solution.push_back(start_coord);

    // Reverse the solution vector so it goes from start to end
    reverse(solution.begin(), solution.end());
}

HexBoard::~HexBoard() {
    for (auto kv : cells) {
        HexCell* cell = kv.second;
        delete cell;
    }
}

vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    return {
        {coord.first, coord.second - 1},
        {coord.first + 1, coord.second - 1},
        {coord.first + 1, coord.second},
        {coord.first, coord.second + 1},
        {coord.first - 1, coord.second + 1},
        {coord.first - 1, coord.second}};
}

HexCell* HexBoard::chooseNeighbour(HexCell* cell, const map<pair<int, int>, bool>& visited, double branch_prob) const {
    vector<HexCell*> neigh_same_dist;
    vector<HexCell*> neigh_diff_dist;

    for (HexCell* neigh_cell : cell->neighbours) {
        if (neigh_cell && visited.find({neigh_cell->q, neigh_cell->r}) == visited.end()) {
            if (neigh_cell->distance(cells.at(start_coord)) == cell->distance(cells.at(start_coord))) {
                neigh_same_dist.push_back(neigh_cell);
            } else {
                neigh_diff_dist.push_back(neigh_cell);
            }
        }
    }

    if (neigh_same_dist.empty() && neigh_diff_dist.empty()) {
        return nullptr;
    } else if (neigh_same_dist.empty()) {
        int idx = rand() % neigh_diff_dist.size();
        return neigh_diff_dist[idx];
    } else if (neigh_diff_dist.empty()) {
        int idx = rand() % neigh_same_dist.size();
        return neigh_same_dist[idx];
    } else {
        std::discrete_distribution<int> dist({branch_prob, 1 - branch_prob});
        std::mt19937 gen(rand());

        int choice = dist(gen);

        if (choice == 0) {
            int idx = rand() % neigh_diff_dist.size();
            return neigh_diff_dist[idx];
        } else {
            int idx = rand() % neigh_same_dist.size();
            return neigh_same_dist[idx];
        }
    }
}