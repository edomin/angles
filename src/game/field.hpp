#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "app.hpp"
#include "draw.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace game {

class Field {
    public:
        enum class cell_t {
            EMPTY,
            PLAYER,
            COMPUTER,
        };
        static constexpr unsigned ROWS_COUNT = 8;
        static constexpr unsigned COLS_COUNT = 8;

    private:
        static constexpr cell_t CELLS_INITIAL[ROWS_COUNT][COLS_COUNT] = {
            {cell_t::PLAYER, cell_t::PLAYER, cell_t::PLAYER, cell_t::EMPTY, cell_t::EMPTY, cell_t::EMPTY,    cell_t::EMPTY,    cell_t::EMPTY},
            {cell_t::PLAYER, cell_t::PLAYER, cell_t::PLAYER, cell_t::EMPTY, cell_t::EMPTY, cell_t::EMPTY,    cell_t::EMPTY,    cell_t::EMPTY},
            {cell_t::PLAYER, cell_t::PLAYER, cell_t::PLAYER, cell_t::EMPTY, cell_t::EMPTY, cell_t::EMPTY,    cell_t::EMPTY,    cell_t::EMPTY},
            {cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY, cell_t::EMPTY, cell_t::EMPTY,    cell_t::EMPTY,    cell_t::EMPTY},
            {cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY, cell_t::EMPTY, cell_t::EMPTY,    cell_t::EMPTY,    cell_t::EMPTY},
            {cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY, cell_t::EMPTY, cell_t::COMPUTER, cell_t::COMPUTER, cell_t::COMPUTER},
            {cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY, cell_t::EMPTY, cell_t::COMPUTER, cell_t::COMPUTER, cell_t::COMPUTER},
            {cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY,  cell_t::EMPTY, cell_t::EMPTY, cell_t::COMPUTER, cell_t::COMPUTER, cell_t::COMPUTER},
        };

        cell_t cells[ROWS_COUNT][COLS_COUNT];

    public:
        Field();
        ~Field();

        void set_cell(unsigned row, unsigned col, cell_t value);
        void unset_cell(unsigned row, unsigned col);

        bool can_move(cell_t required_cell_type, unsigned row, unsigned col) const;
        unsigned get_rows_count() const;
        unsigned get_cols_count() const;
        bool is_available(unsigned row, unsigned col) const;
        bool is_empty(unsigned row, unsigned col) const;
        bool is_player(unsigned row, unsigned col) const;
        bool is_computer(unsigned row, unsigned col) const;
        bool is_adjacents(unsigned row1, unsigned col1, unsigned row2, unsigned col2) const;
        cell_t get_cell(unsigned row, unsigned col) const;
};

} // game::

#endif // GAME_FIELD_HPP
