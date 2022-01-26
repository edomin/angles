#include "sprite.hpp"

Sprite::Sprite(const Spritesheet &_spritesheet, unsigned clip_index)
: spritesheet(&_spritesheet)
, upper_left_u()
, upper_left_v()
, upper_right_u()
, upper_right_v()
, lower_left_u()
, lower_left_v()
, lower_right_u()
, lower_right_v() {
    float texture_width = spritesheet->get_texture()->get_width();
    float texture_height = spritesheet->get_texture()->get_height();
    float clip_x = spritesheet->get_clip_x(clip_index);
    float clip_y = spritesheet->get_clip_y(clip_index);
    float clip_width = spritesheet->get_clip_width();
    float clip_height = spritesheet->get_clip_height();

    upper_left_u = clip_x / texture_width;
    upper_left_v = clip_y / texture_height;
    upper_right_u = (clip_x + clip_width) / texture_width;
    upper_right_v = clip_y / texture_height;
    lower_left_u = clip_x / texture_width;
    lower_left_v = (clip_y + clip_height) / texture_height;
    lower_right_u = (clip_x + clip_width) / texture_width;
    lower_right_v = (clip_y + clip_height) / texture_height;
}

Sprite::~Sprite() {}

const Spritesheet *Sprite::get_spritesheet() const {
    return spritesheet;
}

float Sprite::get_upper_left_u() const {
    return upper_left_u;
}

float Sprite::get_upper_left_v() const {
    return upper_left_v;
}

float Sprite::get_upper_right_u() const {
    return upper_right_u;
}

float Sprite::get_upper_right_v() const {
    return upper_right_v;
}

float Sprite::get_lower_left_u() const {
    return lower_left_u;
}

float Sprite::get_lower_left_v() const {
    return lower_left_v;
}

float Sprite::get_lower_right_u() const {
    return lower_right_u;
}

float Sprite::get_lower_right_v() const {
    return lower_right_v;
}
