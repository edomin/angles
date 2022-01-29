#ifndef VEC2_HPP
#define VEC2_HPP

#include <tuple>

class Vec2 {
    public:
        float x;
        float y;

        Vec2(float _x, float _y);
        Vec2(const Vec2 &other);
        ~Vec2();

        Vec2& operator=(const Vec2 &other);
        Vec2 operator-(const Vec2 &rhs);

        std::tuple<float, float> get_coords();
};

#endif // VEC2_HPP
