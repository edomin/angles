#include "color.hpp"

Color::Color(uint32_t rgba)
: r(static_cast<float>((rgba & 0xFF000000 >> 24)) / 255.0f)
, g(static_cast<float>((rgba & 0x00FF0000 >> 16)) / 255.0f)
, b(static_cast<float>((rgba & 0x0000FF00 >> 8)) / 255.0f)
, a(static_cast<float>((rgba & 0x000000FF)) / 255.0f) {}

Color::~Color() {}

[[gnu::pure]] float Color::get_r() const {
    return r;
}

[[gnu::pure]] float Color::get_g() const {
    return g;
}

[[gnu::pure]] float Color::get_b() const {
    return b;
}

[[gnu::pure]] float Color::get_a() const {
    return a;
}
