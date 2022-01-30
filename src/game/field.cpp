#include "game/field.hpp"

#include <cinttypes>
#include <cstring>
#include <iostream> // delete me
#include <sstream>
#include <utility> // delete me

#include "exception.hpp"

namespace game {

Field::Field()
: content() {
    memcpy(content, CONTENT_INITIAL, sizeof(content_t) * ROWS_COUNT * COLS_COUNT);
}

Field::~Field() {}

void Field::set_content(const Cell &cell, content_t value) {
    content[cell.row][cell.col] = value;
}

void Field::unset_content(const Cell &cell) {
    content[cell.row][cell.col] = content_t::EMPTY;
}

bool Field::can_move(content_t required_content, const Cell &cell) const {
    try {
        if (get_content(cell) != required_content)
            return false;
    }
    catch (const Exception&) {}

    return is_empty(Cell{cell.row - 1, cell.col}) || is_empty(Cell{cell.row + 1, cell.col})
     || is_empty(Cell{cell.row, cell.col - 1}) || is_empty(Cell{cell.row, cell.col + 1});
}

unsigned Field::get_rows_count() const {
    return ROWS_COUNT;
}

unsigned Field::get_cols_count() const {
    return COLS_COUNT;
}

bool Field::is_available(const Cell &cell) const {
    return (cell.row < ROWS_COUNT) && (cell.col < COLS_COUNT);
}

// bool Field::is_empty(unsigned row, unsigned col) const {
//     try {
//         return get_content(row, col) == content_t::EMPTY;
//     }
//     catch (const Exception&) {}

//     return false;
// }

bool Field::is_empty(const Cell &cell) const {
    try {
        return get_content(cell) == content_t::EMPTY;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_player(const Cell &cell) const {
    try {
        return get_content(cell) == content_t::PLAYER;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_computer(const Cell &cell) const {
    try {
        return get_content(cell) == content_t::COMPUTER;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_adjacents(const Cell &cell1, const Cell &cell2) const {
    bool adjacents = false;
    bool cells_available = (cell1.row < ROWS_COUNT) && (cell1.col < COLS_COUNT)
     && (cell2.row < ROWS_COUNT) && (cell2.col < COLS_COUNT);

    if (cells_available) {
        int rows_diff = imaxabs(
         static_cast<int>(cell1.row) - static_cast<int>(cell2.row));
        int cols_diff = imaxabs(
         static_cast<int>(cell1.col) - static_cast<int>(cell2.col));

        adjacents = ((rows_diff == 0) && (cols_diff == 1))
         || ((rows_diff == 1) && (cols_diff == 0));
    }

    return adjacents;
}

Field::content_t Field::get_content(const Cell &cell) const {
    if ((cell.row < ROWS_COUNT) && (cell.col < COLS_COUNT))
        return content[cell.row][cell.col];

    // I want to use std::format, by my gcc don't have <format> header
    std::stringstream msgss;

    msgss << "Out of bounds: row = " << cell.row << ", col = " << cell.col;

    ANG_THROW(msgss.str().c_str());
}

} // game::
