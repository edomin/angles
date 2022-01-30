#include "output_record.hpp"

OutputRecord::OutputRecord(const Sprite &_sprite, const Vec2 &_pos, float _z,
 float _hscale, float _vscale)
: sprite(&_sprite)
, pos(_pos)
, z(_z)
, hscale(_hscale)
, vscale(_vscale) {}

OutputRecord::~OutputRecord() {}
