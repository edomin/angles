#include "game/searching_cell_record.hpp"

namespace game {

SearchingCellRecord::SearchingCellRecord(const Cell &_cell, unsigned _empty_value,
 unsigned _engaged_value)
: cell(_cell)
, empty_value(_empty_value)
, engaged_value(_engaged_value) {}

SearchingCellRecord::~SearchingCellRecord() {}

} // game::
