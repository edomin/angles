#include "game/field.hpp"

#include <cinttypes>
#include <cstring>
#include <sstream>

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

    return is_empty(cell.near_top()) || is_empty(cell.near_bottom())
     || is_empty(cell.near_left()) || is_empty(cell.near_right());
}

[[gnu::const]] unsigned Field::get_rows_count() const {
    return ROWS_COUNT;
}

[[gnu::const]] unsigned Field::get_cols_count() const {
    return COLS_COUNT;
}

[[gnu::pure]] bool Field::is_available(const Cell &cell) const {
    return (cell.row < ROWS_COUNT) && (cell.col < COLS_COUNT);
}

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

[[gnu::pure]] bool Field::is_adjacents(const Cell &cell1, const Cell &cell2) const {
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

Field::content_t Field::get_content(unsigned row, unsigned col) const {
    if ((row < ROWS_COUNT) && (col < COLS_COUNT))
        return content[row][col];

    std::stringstream msgss;

    msgss << "Out of bounds: row = " << row << ", col = " << col;

    ANG_THROW(msgss.str().c_str());
}

Field::content_t Field::get_content(const Cell &cell) const {
    return get_content(cell.row, cell.col);
}

} // game::
