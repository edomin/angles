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

        void set_content(unsigned row, unsigned col, content_t value);
        void unset_content(unsigned row, unsigned col);

        bool can_move(content_t required_content, unsigned row, unsigned col) const;
        unsigned get_rows_count() const;
        unsigned get_cols_count() const;
        bool is_available(unsigned row, unsigned col) const;
        bool is_empty(unsigned row, unsigned col) const;
        bool is_player(unsigned row, unsigned col) const;
        bool is_computer(unsigned row, unsigned col) const;
        bool is_adjacents(unsigned row1, unsigned col1, unsigned row2, unsigned col2) const;
        content_t get_content(unsigned row, unsigned col) const;
};

} // game::

#endif // GAME_FIELD_HPP
