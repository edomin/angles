#include "vec2.hpp"

#include <cmath>
#include <iostream> // delete me

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

Vec2& Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;

    return *this;
}

Vec2& Vec2::operator/=(float num) {
    x /= num;
    y /= num;

    return *this;
}

Vec2 Vec2::operator-(const Vec2 &rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float num) const {
    return Vec2(x * num, y * num);
}

Vec2 Vec2::operator/(float num) const {
    return Vec2(x / num, y / num);
}

Vec2 Vec2::dir_to(const Vec2 &other) const {
    return other - *this;
}

// for direction vectors only
Vec2 &Vec2::normalize() {
    *this /= sqrt(x * x + y * y);

    return *this;
}

float Vec2::dist_to(const Vec2 &other) {
    Vec2 sub = other - *this;

    if (std::isnan(sub.x) || std::isnan(sub.y)) {
        sub.x = 0.0f;
        sub.y = 0.0f;
    }

    return sqrt(sub.x * sub.x + sub.y * sub.y);
}

std::tuple<float, float> Vec2::get_coords() {
    return {x, y};
}
