#ifndef GAME_VEC2_HPP
#define GAME_VEC2_HPP

namespace game {

class Vec2 {
    private:
        float x;
        float y;

    public:
        Vec2(float _x, float _y);
        Vec2(const Vec2 &other);
        ~Vec2();

        Vec2& operator=(const Vec2 &other);
        Vec2 operator-(const Vec2 &rhs);
};

} // game::

#endif // GAME_VEC2_HPP
