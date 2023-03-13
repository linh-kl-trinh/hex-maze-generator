#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    q = Q;
    r = R;
    for (int i = 0; i <= 5; i++) {
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
    path_dist_from_start = 0;
}

void HexCell::link(HexCell* cell) {
    if (cell == nullptr) return;

    if (cell->q == q) {
        if (cell->r == r - 1) {
            links[N] = cell;
            cell->links[S] = this;
        } else if (cell->r == r + 1) {
            links[S] = cell;
            cell->links[N] = this;
        }
    } else if (cell->q == q - 1) {
        if (cell->r == r) {
            links[NW] = cell;
            cell->links[SE] = this;
        } else if (cell->r == r + 1) {
            links[SW] = cell;
            cell->links[NE] = this;
        }
    } else if (cell->q == q + 1) {
        if (cell->r == r) {
            links[SE] = cell;
            cell->links[NW] = this;
        } else if (cell->r == r - 1) {
            links[NE] = cell;
            cell->links[SW] = this;
        }
    } else return;
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    if (cell->q == q) {
        if (cell->r == r - 1) return N;
        else return S;
    } else if (cell->q == q - 1) {
        if (cell->r == r) return NW;
        else return SW;
    } else {
        if (cell->r == r) return SE;
        else return NE;
    }
}

bool HexCell::is_linked(const HexCell* cell) const {
    if (!cell) {
        return false;
    }
    for (int i = 0; i <= 5; i++) {
        if (links[i] == cell) {
            return true;
        }
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    if (!cell) return -1;
    return (abs(q - cell->q) + abs(q + r - cell->q - cell->r) + abs(r - cell->r)) / 2;
}

bool HexCell::is_edge() const {
    for (int i = 0; i <= 5; i++) {
        if (neighbours[i] == nullptr) return true;
    }
    return false;
}