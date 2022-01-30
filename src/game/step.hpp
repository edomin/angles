#ifndef GAME_STEP_HPP
#define GAME_STEP_HPP

#include "game/cell.hpp"

namespace game {

class Step {
    public:
        Cell start;
        Cell dst;

        Step(const Cell &_start, const Cell &_dst);
        ~Step();
};

} // game::

#endif // GAME_STEP_HPP
