#ifndef GAME_LINE_HPP
#define GAME_LINE_HPP

#include "vec2.hpp"

namespace game {

class Line {
    public:
        Vec2 a;
        Vec2 b;

        Line(const Vec2 &_a, const Vec2 &_b);
        ~Line();

        Line& operator=(const Line &other);

        bool shrink_to_b(float len);
};

} // game::

#endif // GAME_LINE_HPP
