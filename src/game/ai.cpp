#include "game/ai.hpp"

#include <cstring>
#include <iomanip>
#include <iostream>

#include "exception.hpp"
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

        if (cell == rec.cell) {
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

bool Ai::update_near_values(const Search &search, Search *new_values,
 unsigned value, const Cell &cell) {
    return update_value(search, new_values, value, cell.near_top())
     || update_value(search, new_values, value, cell.near_bottom())
     || update_value(search, new_values, value, cell.near_left())
     || update_value(search, new_values, value, cell.near_right());
}

// returns true if must stop filling
bool Ai::update_values(Search *search, unsigned *value) {
    unsigned rows_count = field->get_rows_count();
    unsigned cols_count = field->get_cols_count();
    Search   new_values(rows_count, cols_count);
    bool     must_stop = false;

    (*value)--;

    new_values = *search;

    for (unsigned row = 0; (row < rows_count) && !must_stop; row++) {
        for (unsigned col = 0; (col < cols_count) && !must_stop; col++) {
            if (search->at(row, col) != 0) {
                must_stop = update_near_values(*search, &new_values, *value,
                 Cell{row, col});
            }
        }
    }

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

Cell Ai::choose_empty_cell(const Cell &cell) {
    if (!field->can_move(Field::content_t::COMPUTER, cell))
        ANG_THROW("choose_empty_cell(): no empty cells");

    if (field->is_empty(cell.near_top()))
        return cell.near_top();
    else if (field->is_empty(cell.near_bottom()))
        return  cell.near_bottom();
    else if (field->is_empty(cell.near_left()))
        return  cell.near_left();

    return cell.near_right();
}

Step Ai::random_move() {
    for (unsigned row = 0; row < field->get_rows_count(); row++) {
        for (unsigned col = 0; col < field->get_rows_count(); col++) {
            Cell cell(row, col);

            if (field->can_move(Field::content_t::COMPUTER, cell))
                return {cell, choose_empty_cell(cell)};
        }
    }

    return Step::create_idle();
}

std::tuple<unsigned, unsigned, Cell> Ai::find_max_value_cell() {
    unsigned max_value = 0;
    unsigned max_value_search_index;
    Cell     max_value_cell(0, 0);

    for (size_t srch_index = 0; srch_index < SEARCHES_COUNT; srch_index++) {
        for (unsigned row = 0; row < Field::ROWS_COUNT; row++) {
            for (unsigned col = 0; col < Field::COLS_COUNT; col++) {
                Cell cell(row, col);
                bool can_move = field->can_move(Field::content_t::COMPUTER,
                 cell);

                if (can_move && searches[srch_index]->at(cell) > max_value) {
                    max_value = searches[srch_index]->at(cell);
                    max_value_search_index = srch_index;
                    max_value_cell = cell;
                }
            }
        }
    }

    return {max_value, max_value_search_index, max_value_cell};
}

Step Ai::move() {
    Step result = Step::create_idle();
    auto [
        max_value,
        max_value_search_index,
        max_value_cell
    ] = find_max_value_cell();

    if (max_value != 0) {
        unsigned next_value = 0;
        Cell     next_cell(0, 0);
        bool     choosen = false;
        Search  *maxval_srch = searches[max_value_search_index];

        // Не смог придумать, как сделать этот кусок красивее
        if (field->is_empty(max_value_cell.near_top()) && maxval_srch->at(max_value_cell.near_top()) > next_value) {
            next_cell = max_value_cell.near_top();
            choosen = true;
        } else if (field->is_empty(max_value_cell.near_bottom()) && maxval_srch->at(max_value_cell.near_bottom()) > next_value) {
            next_cell = max_value_cell.near_bottom();
            choosen = true;
        } else if (field->is_empty(max_value_cell.near_left()) && maxval_srch->at(max_value_cell.near_left()) > next_value) {
            next_cell = max_value_cell.near_left();
            choosen = true;
        } else if (field->is_empty(max_value_cell.near_right()) && maxval_srch->at(max_value_cell.near_right()) > next_value) {
            next_cell = max_value_cell.near_right();
            choosen = true;
        }

        if (choosen)
            result = {max_value_cell, next_cell};
        else
            max_value = 0;
    }

    if (max_value == 0)
        return random_move();

    return result;
}

Step Ai::process_turn() {
    for (size_t i = 0; i < SEARCHES_COUNT; i++)
        search(i);

    return move();
}

} // game::
