#ifndef OUTPUT_RECORD_HPP
#define OUTPUT_RECORD_HPP

#include "sprite.hpp"
#include "vec2.hpp"

class OutputRecord {
    public:
        const Sprite *sprite;
        Vec2          pos;
        float         z;
        float         hscale;
        float         vscale;

    public:
        OutputRecord(const Sprite &_sprite, const Vec2 &_pos, float _z,
         float _hscale, float _vscale);
        ~OutputRecord();
};

#endif // OUTPUT_RECORD_HPP
