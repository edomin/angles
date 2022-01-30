#ifndef GAME_SEARCHING_CELL_RECORD_HPP
#define GAME_SEARCHING_CELL_RECORD_HPP

#include "game/cell.hpp"

namespace game {

class SearchingCellRecord {
    public:
        Cell     cell;
        unsigned empty_value;
        unsigned engaged_value;

        SearchingCellRecord(const Cell &_cell, unsigned _empty_value,
         unsigned _engaged_value);
        ~SearchingCellRecord();
};

} // game::

#endif // GAME_SEARCHING_CELL_RECORD_HPP
