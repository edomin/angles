#include "game/line.hpp"

#include <iostream> // delete me

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

// returns true if line was overshrinked
bool Line::shrink_to_b(float len) {
    float distance_old = a.dist_to(b);
    float distance_new;

    a += a.dir_to(b).normalize() * len;

    distance_new = a.dist_to(b);

    return distance_new >= distance_old;
}

} // game::
