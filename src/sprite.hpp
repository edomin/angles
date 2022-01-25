#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "spritesheet.hpp"

class Sprite {
    private:
        const Spritesheet *spritesheet;
        float              upper_left_u;
        float              upper_left_v;
        float              upper_right_u;
        float              upper_right_v;
        float              lower_left_u;
        float              lower_left_v;
        float              lower_right_u;
        float              lower_right_v;

    public:
        Sprite(const Spritesheet &_spritesheet, unsigned clip_index);
        ~Sprite();

        const Spritesheet *get_spritesheet() const;
        float get_upper_left_u() const;
        float get_upper_left_v() const;
        float get_upper_right_u() const;
        float get_upper_right_v() const;
        float get_lower_left_u() const;
        float get_lower_left_v() const;
        float get_lower_right_u() const;
        float get_lower_right_v() const;
};

#endif // SPRITE_HPP
