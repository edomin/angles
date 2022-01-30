#ifndef GAME_AI_HPP
#define GAME_AI_HPP

#include <vector>
#include <unordered_map>

#include "game/cell.hpp"
#include "game/field.hpp"
#include "game/search.hpp"
#include "game/step.hpp"

namespace game {

class Ai {
    private:
        static constexpr unsigned SEARCHES_COUNT = 9;

        Field                    *field;
        std::vector<Search *>     searches;

        unsigned get_cell_starting_value(const Cell &cell);
        bool update_value(const Search &search, Search *new_values,
         unsigned value, const Cell &cell);
        bool update_near_values(const Search &search, Search *new_values,
         unsigned value, const Cell &cell);
        bool update_values(Search *search, unsigned *value);
        void search(unsigned search_index);
        Cell choose_empty_cell(const Cell &cell);
        Step random_move();
        std::tuple<unsigned, unsigned, Cell> find_max_value_cell();
        Step move();

    public:
        Ai(Field &_field);
        ~Ai();

        Step process_turn();
};

} // game::

#endif // GAME_AI_HPP
