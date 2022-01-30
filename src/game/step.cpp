#include "game/step.hpp"

namespace game {

Step::Step(const Cell &_start, const Cell &_dst)
: start(_start)
, dst(_dst) {}

Step::~Step() {}

bool Step::is_idle() {
    return start == dst;
}

} // game::
