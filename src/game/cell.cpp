#include "game/cell.hpp"

namespace game {

Cell::Cell(unsigned _row, unsigned _col)
: row(_row)
, col(_col) {}

Cell::Cell(const Cell &other)
: row(other.row)
, col(other.col) {}

Cell::~Cell() {}

Cell& Cell::operator=(const Cell &other) {
    if (&other != this) {
        row = other.row;
        col = other.col;
    }

    return *this;
}

[[gnu::pure]] bool Cell::operator==(const Cell &other) const {
    return (row == other.row) && (col == other.col);
}

Cell Cell::near_top() const {
    return Cell{row - 1, col};
}

Cell Cell::near_bottom() const {
    return Cell{row + 1, col};
}

Cell Cell::near_left() const {
    return Cell{row, col - 1};
}

Cell Cell::near_right() const {
    return Cell{row, col + 1};
}

} // game::
