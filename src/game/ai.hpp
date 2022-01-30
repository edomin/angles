#ifndef GAME_AI_HPP
#define GAME_AI_HPP

#include <vector>
#include <tuple>
#include <unordered_map>

#include "game/cell.hpp"
#include "game/field.hpp"
#include "game/search.hpp"

namespace game {

class Ai {
    private:
        static constexpr unsigned SEARCHES_COUNT = 9;

        // typedef unsigned search_t[Field::ROWS_COUNT][Field::COLS_COUNT];
        // typedef std::map<Cell, unsigned> search_t;

        Field                *field;
        std::vector<Search *> searches;
        // search_t searches[SEARCHES_COUNT];

        unsigned get_cell_starting_value(const Cell &cell);
        bool update_value(const Search &search, Search *new_values,
         unsigned value, const Cell &cell);
        bool update_values(Search *search, unsigned *value);
        void search(unsigned search_index);
        std::tuple<Cell, Cell> move();

        void debug_output();

    public:
        Ai(Field &_field);
        ~Ai();

        std::tuple<Cell, Cell> process_turn();
};

} // game::

#endif // GAME_AI_HPP
