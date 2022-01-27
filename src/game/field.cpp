#include "game/field.hpp"

#include <cstring>
#include <iostream> // delete me
#include <utility> //delete me

namespace game {

Field::Field()
: cells() {
    memcpy(cells, CELLS_INITIAL, sizeof(cell_t) * ROWS_COUNT * COLS_COUNT);
}

Field::~Field() {}

void Field::set_cell(unsigned row, unsigned col, cell_t value) {
    cells[row][col] = value;
}

void Field::unsset_cell(unsigned row, unsigned col) {
    cells[row][col] = cell_t::EMPTY;
}

unsigned Field::get_rows_count() {
    return ROWS_COUNT;
}

unsigned Field::get_cols_count() {
    return COLS_COUNT;
}

Field::cell_t Field::get_cell(unsigned row, unsigned col) {
    return cells[row][col];
}

} // game::
