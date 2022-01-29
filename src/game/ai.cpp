#include "game/ai.hpp"

#include <cstring>
#include <iomanip>
#include <iostream>

#include "debug.hpp" //delete me

namespace {
    typedef std::tuple<
        unsigned, // row
        unsigned, // col
        unsigned, // starting value if empty
        unsigned  // starting value if engaged by player
    > starting_cell_data_t;

    static const std::vector<starting_cell_data_t> STARTING_CELLS = {
        {0, 0, 150, 105}, {0, 1, 140, 104}, {0, 2, 130, 103},
        {1, 0, 140, 104}, {1, 1, 130, 103}, {1, 2, 120, 102},
        {2, 0, 130, 103}, {2, 1, 120, 102}, {2, 2, 110, 101},
    };
}

namespace game {

Ai::Ai(Field &_field)
: field(&_field)
, searches() {}

Ai::~Ai() {}

unsigned Ai::get_cell_starting_value(unsigned row, unsigned col) {
    unsigned result = 0;

    for (unsigned i = 0; i < SEARCHES_COUNT; i++) {
        auto [srch_row, srch_col, starting_value, _] = STARTING_CELLS.at(i);

        if ((row == srch_row) && (col == srch_col)) {
            result = starting_value;
            break;
        }
    }

    return result;
}

bool Ai::update_value(unsigned (*srch)[Field::COLS_COUNT], unsigned (*new_values)[Field::COLS_COUNT], unsigned *value, unsigned row, unsigned col) {
    bool must_stop = false;

    if (!field->is_available(row, col))
        return false;

    if (srch[row][col] != 0)
        return false;

    // std::cout << "row: " << row << " col: " << col << " is_empty: " << field->is_empty(row, col) << std::endl;

    if (field->is_empty(row, col)) {
        new_values[row][col] = *value;
    } else if (field->is_computer(row, col)) {
        std::cout << "get_cell_starting_value(row, col): " << get_cell_starting_value(row, col) << std::endl;
        std::cout << "*value: " << *value << std::endl;
        if (get_cell_starting_value(row, col) < *value) {
            new_values[row][col] = *value;

            must_stop = true;
        }
    }

    // std::cout << "must_stop: " << must_stop << std::endl;

    return must_stop;
}

// returns true if must stop filling
bool Ai::update_values(unsigned (*srch)[Field::COLS_COUNT], unsigned *value) {
    search_t new_values;
    bool     must_stop = false;
    bool     break2 = false;

    // std::cout << "*value: " << *value << std::endl;

    (*value)--;

    memcpy(new_values, srch, sizeof(search_t));

    for (unsigned row = 0; (row < Field::ROWS_COUNT) && !break2; row++) {
        for (unsigned col = 0; col < Field::COLS_COUNT; col++) {
            if (srch[row][col] != 0) {
                if (update_value(srch, new_values, value, row - 1, col)) {
                    must_stop = true;
                    break2 = true;
                    break;
                }
                if (update_value(srch, new_values, value, row + 1, col)) {
                    must_stop = true;
                    break2 = true;
                    continue;
                    break;
                }
                if (update_value(srch, new_values, value, row, col - 1)) {
                    must_stop = true;
                    break2 = true;
                    continue;
                    break;
                }
                if (update_value(srch, new_values, value, row, col + 1)) {
                    must_stop = true;
                    break2 = true;
                    continue;
                    break;
                }
            }
        }
    }

    if (memcmp(new_values, srch, sizeof(search_t)) == 0)
        return true;

    memcpy(srch, new_values, sizeof(search_t));

    // (*value)--;
    return must_stop;
}

void Ai::search(unsigned search_index) {
    unsigned (*srch)[Field::COLS_COUNT] = searches[search_index];
    auto [start_row, start_col, value_empty, value_engaged] = STARTING_CELLS[search_index];
    bool must_stop = false;
    unsigned value;

    memset(srch, 0, sizeof(search_t));


    if (field->is_empty(start_row, start_col)) {
        value = value_empty;
    } else if (field->is_player(start_row, start_col)) {
        value = value_engaged;
    } else {
        // value = 0;
        must_stop = true;
    }

    if (!must_stop)
        srch[start_row][start_col] = value;

    // std::cout << "value: " << value << std::endl;

    while (!must_stop)
        must_stop = update_values(srch, &value);

    // for (unsigned row = 0; row < Field::ROWS_COUNT; row++) {
    //     for (unsigned col = 0; col < Field::COLS_COUNT; col++) {

    //     }
    // }
}

void Ai::debug_output() {
    std::ios fmt(nullptr);

    std::cout << "DEBUG: " << std::endl;

    fmt.copyfmt(std::cout);
    for (size_t search_index = 0; search_index < SEARCHES_COUNT; search_index++) {
        std::cout << "search " << search_index << ":" << std::endl;
        // std::cout << std::setw(4);
        for (size_t row = 0; row < Field::ROWS_COUNT; row++) {
            for (size_t col = 0; col < Field::COLS_COUNT; col++)
                std::cout << std::setw(4) << searches[search_index][row][col];
            std::cout << std::endl;
        }
        std::cout.copyfmt(fmt);
    }
}

// Этот кусок был написан в день сдачи в 5 часов утра после 3-х выпитых редбулов :-(
void Ai::move() {
    unsigned max_value = 0;
    unsigned max_value_search_index;
    unsigned max_value_row;
    unsigned max_value_col;

    for (size_t search_index = 0; search_index < SEARCHES_COUNT; search_index++) {
        for (size_t row = 0; row < Field::ROWS_COUNT; row++) {
            for (size_t col = 0; col < Field::COLS_COUNT; col++) {
                if (field->can_move(Field::content_t::COMPUTER, row, col) && searches[search_index][row][col] > max_value) {
                    max_value = searches[search_index][row][col];
                    // if (field->is_available(row - 1, col))
                    //     max_value_up = searches[search_index][row - 1][col];
                    // if (field->is_available(row + 1, col))
                    //     max_value_down = searches[search_index][row + 1][col];
                    // if (field->is_available(row, col - 1))
                    //     max_value_left = searches[search_index][row][col - 1];
                    // if (field->is_available(row, col + 1))
                    //     max_value_right = searches[search_index][row][col + 1];
                    max_value_search_index = search_index;
                    max_value_row = row;
                    max_value_col = col;
                }
            }
        }
    }

    if (max_value != 0) {
        unsigned next_value = 0;
        unsigned next_row;
        unsigned next_col;
        bool choosen = false;

        if (field->is_empty(max_value_row - 1, max_value_col) && searches[max_value_search_index][max_value_row - 1][max_value_col] > next_value) {
            next_row = max_value_row - 1;
            next_col = max_value_col;
            choosen = true;
        }
        if (field->is_empty(max_value_row + 1, max_value_col) && searches[max_value_search_index][max_value_row + 1][max_value_col] > next_value) {
            next_row = max_value_row + 1;
            next_col = max_value_col;
            choosen = true;
        }
        if (field->is_empty(max_value_row, max_value_col - 1) && searches[max_value_search_index][max_value_row][max_value_col - 1] > next_value) {
            next_row = max_value_row;
            next_col = max_value_col - 1;
            choosen = true;
        }
        if (field->is_empty(max_value_row, max_value_col + 1) && searches[max_value_search_index][max_value_row][max_value_col + 1] > next_value) {
            next_row = max_value_row;
            next_col = max_value_col + 1;
            choosen = true;
        }

        if (choosen) {
            field->unset_content(max_value_row, max_value_col);
            field->set_content(next_row, next_col, Field::content_t::COMPUTER);
        } else {
            max_value = 0;
        }
    }

    if (max_value == 0) {
        // random move
        for (unsigned row = 0; row < field->get_rows_count(); row++) {
            for (unsigned col = 0; col < field->get_rows_count(); col++) {
                if (field->can_move(Field::content_t::COMPUTER, row, col)) {
                    unsigned next_row;
                    unsigned next_col;

                    if (field->is_empty(row - 1, col)) {
                        next_row = row - 1;
                        next_col = col;
                    }
                    if (field->is_empty(row + 1, col)) {
                        next_row = row + 1;
                        next_col = col;
                    }
                    if (field->is_empty(row, col - 1)) {
                        next_row = row;
                        next_col = col - 1;
                    }
                    if (field->is_empty(row, col + 1)) {
                        next_row = row;
                        next_col = col + 1;
                    }

                    field->unset_content(row, col);
                    field->set_content(next_row, next_col, Field::content_t::COMPUTER);

                    return;
                }
            }
        }
    }
}

void Ai::process_turn() {
    for (size_t i = 0; i < SEARCHES_COUNT; i++)
        search(i);

    move();

    debug_output();
}

} // game::
