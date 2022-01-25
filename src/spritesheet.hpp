#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <utility>
#include <vector>

#include "texture.hpp"

class Spritesheet {
    private:
        const Texture                             *texture;
        unsigned                                   clip_width;
        unsigned                                   clip_height;
        std::vector<std::pair<unsigned, unsigned>> clip_coords;

    public:
        Spritesheet(const Texture &_texture, unsigned _clip_width,
         unsigned _clip_height);
        ~Spritesheet();

        const Texture *get_texture() const;
        unsigned get_clip_x(unsigned clip_index) const;
        unsigned get_clip_y(unsigned clip_index) const;
        unsigned get_clip_width() const;
        unsigned get_clip_height() const;
};

#endif // SPRITESHEET_HPP
