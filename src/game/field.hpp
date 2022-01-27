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

    private:
        static constexpr unsigned ROWS_COUNT = 8;
        static constexpr unsigned COLS_COUNT = 8;
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
        void unsset_cell(unsigned row, unsigned col);

        unsigned get_rows_count();
        unsigned get_cols_count();
        cell_t get_cell(unsigned row, unsigned col);
};

} // game::

#endif // GAME_FIELD_HPP
