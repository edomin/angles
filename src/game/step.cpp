#include "game/step.hpp"

namespace game {

Step::Step(const Cell &_start, const Cell &_dst)
: start(_start)
, dst(_dst) {}

Step::~Step() {}

Step Step::create_idle() {
    return Step({0, 0}, {0, 0});
}

bool Step::is_idle() {
    return start == dst;
}

} // game::
