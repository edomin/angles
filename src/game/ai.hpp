#ifndef GAME_AI_HPP
#define GAME_AI_HPP

#include "game/field.hpp"

namespace game {

class Ai {
    private:
        static constexpr unsigned SEARCHES_COUNT = 9;

        typedef unsigned search_t[Field::ROWS_COUNT][Field::COLS_COUNT];

        Field   *field;
        search_t searches[SEARCHES_COUNT];

        unsigned get_cell_starting_value(unsigned row, unsigned col);
        bool update_value(unsigned (*srch)[Field::COLS_COUNT], unsigned (*new_values)[Field::COLS_COUNT], unsigned *value, unsigned row, unsigned col);
        bool update_values(unsigned (*srch)[Field::COLS_COUNT], unsigned *value);
        void search(unsigned search_index);
        void move();

        void debug_output();

    public:
        Ai(Field &_field);
        ~Ai();

        void process_turn();
};

} // game::

#endif // GAME_AI_HPP
