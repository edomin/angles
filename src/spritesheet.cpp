#include "spritesheet.hpp"

Spritesheet::Spritesheet(const Texture &_texture, unsigned _clip_width,
 unsigned _clip_height)
: texture(&_texture)
, clip_width(_clip_width)
, clip_height(_clip_height)
, clip_coords() {
    unsigned clips_in_row = texture->get_width() / clip_width;
    unsigned clips_in_col = texture->get_height() / clip_height;
    unsigned clips_count = clips_in_row * clips_in_col;

    for (unsigned i = 0; i < clips_count; i++) {
        unsigned clip_y = i / clips_in_row * clip_height;
        unsigned clip_x = i % clips_in_row * clip_width;

        clip_coords.push_back({clip_x, clip_y});
    }
}

Spritesheet::~Spritesheet() {}

const Texture *Spritesheet::get_texture() const {
    return texture;
}

unsigned Spritesheet::get_clip_x(unsigned clip_index) const {
    return clip_coords.at(clip_index).first;
}

unsigned Spritesheet::get_clip_y(unsigned clip_index) const {
    return clip_coords.at(clip_index).second;
}

unsigned Spritesheet::get_clip_width() const {
    return clip_width;
}

unsigned Spritesheet::get_clip_height() const {
    return clip_height;
}
