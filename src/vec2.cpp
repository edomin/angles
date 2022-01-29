#include "vec2.hpp"

Vec2::Vec2(float _x, float _y)
: x(_x)
, y(_y) {}

Vec2::Vec2(const Vec2 &other)
: x(other.x)
, y(other.y) {}

Vec2::~Vec2() {}

Vec2& Vec2::operator=(const Vec2 &other) {
    if (&other != this) {
        x = other.x;
        y = other.y;
    }

    return *this;
}

Vec2 Vec2::operator-(const Vec2 &rhs) {
    return Vec2{x - rhs.x, y - rhs.y};
}

std::tuple<float, float> Vec2::get_coords() {
    return {x, y};
}
