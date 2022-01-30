#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include "app.hpp"
#include "draw.hpp"
#include "game/cell.hpp"
#include "res_keeper.hpp"
#include "timer.hpp"
#include "window.hpp"

namespace game {

class Field {
    public:
        enum class content_t {
            EMPTY,
            PLAYER,
            COMPUTER,
        };
        static constexpr unsigned ROWS_COUNT = 8;
        static constexpr unsigned COLS_COUNT = 8;

    private:
        static constexpr content_t CONTENT_INITIAL[ROWS_COUNT][COLS_COUNT] = {
            {content_t::PLAYER, content_t::PLAYER, content_t::PLAYER, content_t::EMPTY, content_t::EMPTY, content_t::EMPTY,    content_t::EMPTY,    content_t::EMPTY},
            {content_t::PLAYER, content_t::PLAYER, content_t::PLAYER, content_t::EMPTY, content_t::EMPTY, content_t::EMPTY,    content_t::EMPTY,    content_t::EMPTY},
            {content_t::PLAYER, content_t::PLAYER, content_t::PLAYER, content_t::EMPTY, content_t::EMPTY, content_t::EMPTY,    content_t::EMPTY,    content_t::EMPTY},
            {content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY, content_t::EMPTY, content_t::EMPTY,    content_t::EMPTY,    content_t::EMPTY},
            {content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY, content_t::EMPTY, content_t::EMPTY,    content_t::EMPTY,    content_t::EMPTY},
            {content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY, content_t::EMPTY, content_t::COMPUTER, content_t::COMPUTER, content_t::COMPUTER},
            {content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY, content_t::EMPTY, content_t::COMPUTER, content_t::COMPUTER, content_t::COMPUTER},
            {content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY,  content_t::EMPTY, content_t::EMPTY, content_t::COMPUTER, content_t::COMPUTER, content_t::COMPUTER},
        };

        content_t content[ROWS_COUNT][COLS_COUNT];

    public:
        Field();
        ~Field();

        void set_content(const Cell &cell, content_t value);
        void unset_content(const Cell &cell);

        bool can_move(content_t required_content, const Cell &cell) const;
        unsigned get_rows_count() const;
        unsigned get_cols_count() const;
        bool is_available(const Cell &cell) const;
        bool is_empty(const Cell &cell) const;
        // bool is_empty(unsigned row, unsigned col) const;
        bool is_player(const Cell &cell) const;
        bool is_computer(const Cell &cell) const;
        bool is_adjacents(const Cell &cell1, const Cell &cell2) const;
        content_t get_content(const Cell &cell) const;
};

} // game::

#endif // GAME_FIELD_HPP
