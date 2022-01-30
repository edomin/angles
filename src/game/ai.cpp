#include "game/ai.hpp"

#include <cstring>
#include <iomanip>
#include <iostream>

#include "debug.hpp" //delete me
#include "game/searching_cell_record.hpp"

namespace {
    const std::vector<game::SearchingCellRecord> SEARCHING_CELLS = {
        {{0, 0}, 150, 105}, {{0, 1}, 140, 104}, {{0, 2}, 130, 103},
        {{1, 0}, 140, 104}, {{1, 1}, 130, 103}, {{1, 2}, 120, 102},
        {{2, 0}, 130, 103}, {{2, 1}, 120, 102}, {{2, 2}, 110, 101},
    };
}

namespace game {

Ai::Ai(Field &_field)
: field(&_field)
, searches() {
    for (unsigned i = 0; i < SEARCHES_COUNT; i++) {
        searches.push_back(
         new Search(field->get_rows_count(), field->get_rows_count()));
    }
}

Ai::~Ai() {}

unsigned Ai::get_cell_starting_value(const Cell &cell) {
    unsigned result = 0;

    for (unsigned i = 0; i < SEARCHES_COUNT; i++) {
        SearchingCellRecord rec = SEARCHING_CELLS.at(i);
        Cell               *srch_cell = &rec.cell;

        if (cell == *srch_cell) {
            result = rec.empty_value;
            break;
        }
    }

    return result;
}

bool Ai::update_value(const Search &search, Search *new_values, unsigned value,
 const Cell &cell) {
    bool must_stop = false;

    if (!field->is_available(cell))
        return false;

    if (search.at(cell) != 0)
        return false;

    if (field->is_empty(cell)) {
        new_values->set(cell, value);
    } else if (field->is_computer(cell)) {
        if (get_cell_starting_value(cell) < value) {
            new_values->set(cell, value);

            must_stop = true;
        }
    }

    return must_stop;
}

// returns true if must stop filling
bool Ai::update_values(Search *search, unsigned *value) {
    Search new_values(field->get_rows_count(), field->get_cols_count());
    bool   must_stop = false;

    (*value)--;

    new_values = *search;

    for (unsigned row = 0; (row < field->get_rows_count()); row++) {
        for (unsigned col = 0; col < field->get_cols_count(); col++) {
            if (search->at(row, col) != 0) {
                if (update_value(*search, &new_values, *value, Cell{row - 1, col}))
                    must_stop = true;
                else if (update_value(*search, &new_values, *value, Cell{row + 1, col}))
                    must_stop = true;
                else if (update_value(*search, &new_values, *value, Cell{row, col - 1}))
                    must_stop = true;
                else if (update_value(*search, &new_values, *value, Cell{row, col + 1}))
                    must_stop = true;
                if (must_stop)
                    goto outer_break;
            }
        }
    }
outer_break:

    if (new_values == *search)
        return true;

    *search = new_values;

    return must_stop;
}

void Ai::search(unsigned search_index) {
    Search                    *search = searches[search_index];
    const SearchingCellRecord *rec = &SEARCHING_CELLS[search_index];
    const Cell                *start_cell = &rec->cell;
    bool                       must_stop = false;
    unsigned                   value;

    search->clear();


    if (field->is_empty(*start_cell))
        value = rec->empty_value;
    else if (field->is_player(*start_cell))
        value = rec->engaged_value;
    else
        must_stop = true;

    if (!must_stop)
        search->set(*start_cell, value);

    while (!must_stop)
        must_stop = update_values(search, &value);
}

void Ai::debug_output() {
    std::ios fmt(nullptr);

    std::cout << "DEBUG: " << std::endl;

    fmt.copyfmt(std::cout);
    for (size_t search_index = 0; search_index < SEARCHES_COUNT; search_index++) {
        std::cout << "search " << search_index << ":" << std::endl;

        for (size_t row = 0; row < Field::ROWS_COUNT; row++) {
            for (size_t col = 0; col < Field::COLS_COUNT; col++)
                std::cout << std::setw(4) << searches[search_index]->at(row, col);
            std::cout << std::endl;
        }
        std::cout.copyfmt(fmt);
    }
}

std::tuple<Cell, Cell> Ai::move() {
    unsigned max_value = 0;
    unsigned max_value_search_index;
    unsigned max_value_row;
    unsigned max_value_col;
    Cell result_pos(0.0f, 0.0f);
    Cell result_dst(0.0f, 0.0f);

    for (size_t search_index = 0; search_index < SEARCHES_COUNT; search_index++) {
        for (unsigned row = 0; row < Field::ROWS_COUNT; row++) {
            for (unsigned col = 0; col < Field::COLS_COUNT; col++) {
                if (field->can_move(Field::content_t::COMPUTER, Cell{row, col}) && searches[search_index]->at(row, col) > max_value) {
                    max_value = searches[search_index]->at(row, col);
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

        if (field->is_empty(Cell{max_value_row - 1, max_value_col}) && searches[max_value_search_index]->at(max_value_row - 1, max_value_col) > next_value) {
            next_row = max_value_row - 1;
            next_col = max_value_col;
            choosen = true;
        } else if (field->is_empty(Cell{max_value_row + 1, max_value_col}) && searches[max_value_search_index]->at(max_value_row + 1, max_value_col) > next_value) {
            next_row = max_value_row + 1;
            next_col = max_value_col;
            choosen = true;
        } else if (field->is_empty(Cell{max_value_row, max_value_col - 1}) && searches[max_value_search_index]->at(max_value_row, max_value_col - 1) > next_value) {
            next_row = max_value_row;
            next_col = max_value_col - 1;
            choosen = true;
        } else if (field->is_empty(Cell{max_value_row, max_value_col + 1}) && searches[max_value_search_index]->at(max_value_row, max_value_col + 1) > next_value) {
            next_row = max_value_row;
            next_col = max_value_col + 1;
            choosen = true;
        }

        if (choosen) {
            field->unset_content(Cell{max_value_row, max_value_col});
            result_pos = {max_value_row, max_value_col};
            result_dst = {next_row, next_col};
        } else {
            max_value = 0;
        }
    }

    if (max_value == 0) {
        // random move
        for (unsigned row = 0; row < field->get_rows_count(); row++) {
            for (unsigned col = 0; col < field->get_rows_count(); col++) {
                if (field->can_move(Field::content_t::COMPUTER, Cell{row, col})) {
                    unsigned next_row;
                    unsigned next_col;

                    if (field->is_empty(Cell{row - 1, col})) {
                        next_row = row - 1;
                        next_col = col;
                    }
                    if (field->is_empty(Cell{row + 1, col})) {
                        next_row = row + 1;
                        next_col = col;
                    }
                    if (field->is_empty(Cell{row, col - 1})) {
                        next_row = row;
                        next_col = col - 1;
                    }
                    if (field->is_empty(Cell{row, col + 1})) {
                        next_row = row;
                        next_col = col + 1;
                    }

                    field->unset_content(Cell{row, col});

                    result_pos = {row, col};
                    result_dst = {next_row, next_col};

                    return {result_pos, result_dst};
                }
            }
        }
    }

    return {result_pos, result_dst};
}

std::tuple<Cell, Cell> Ai::process_turn() {
    for (size_t i = 0; i < SEARCHES_COUNT; i++)
        search(i);

    return move();

    // debug_output();
}

} // game::
