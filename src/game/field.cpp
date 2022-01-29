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

void Field::set_content(unsigned row, unsigned col, content_t value) {
    content[row][col] = value;
}

void Field::unset_content(unsigned row, unsigned col) {
    content[row][col] = content_t::EMPTY;
}

bool Field::can_move(content_t required_content, unsigned row, unsigned col) const {
    try {
        if (get_content(row, col) != required_content)
            return false;
    }
    catch (const Exception&) {}

    return is_empty(row - 1, col) || is_empty(row + 1, col)
     || is_empty(row, col - 1) || is_empty(row, col + 1);
}

unsigned Field::get_rows_count() const {
    return ROWS_COUNT;
}

unsigned Field::get_cols_count() const {
    return COLS_COUNT;
}

bool Field::is_available(unsigned row, unsigned col) const {
    return (row < ROWS_COUNT) && (col < COLS_COUNT);
}

bool Field::is_empty(unsigned row, unsigned col) const {
    try {
        return get_content(row, col) == content_t::EMPTY;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_player(unsigned row, unsigned col) const {
    try {
        return get_content(row, col) == content_t::PLAYER;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_computer(unsigned row, unsigned col) const {
    try {
        return get_content(row, col) == content_t::COMPUTER;
    }
    catch (const Exception&) {}

    return false;
}

bool Field::is_adjacents(unsigned row1, unsigned col1, unsigned row2, unsigned col2) const {
    bool adjacents = false;
    bool cells_available = (row1 < ROWS_COUNT) && (col1 < COLS_COUNT)
     && (row2 < ROWS_COUNT) && (col2 < COLS_COUNT);

    if (cells_available) {
        int rows_diff = imaxabs(
         static_cast<int>(row1) - static_cast<int>(row2));
        int cols_diff = imaxabs(
         static_cast<int>(col1) - static_cast<int>(col2));

        adjacents = ((rows_diff == 0) && (cols_diff == 1))
         || ((rows_diff == 1) && (cols_diff == 0));
    }

    return adjacents;
}

Field::content_t Field::get_content(unsigned row, unsigned col) const {
    if ((row < ROWS_COUNT) && (col < COLS_COUNT))
        return content[row][col];

    // I want to use std::format, by my gcc don't have <format> header
    std::stringstream msgss;

    msgss << "Out of bounds: row = " << row << ", col = " << col;

    ANG_THROW(msgss.str().c_str());
}

} // game::
