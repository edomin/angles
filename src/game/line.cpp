#include "game/line.hpp"

namespace game {

Line::Line(const Vec2 &_a, const Vec2 &_b)
: a(_a)
, b(_b) {}

Line::~Line() {}

Line& Line::operator=(const Line &other) {
    if (&other != this) {
        a = other.a;
        b = other.b;
    }

    return *this;
}

} // game::
