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
        Vec2& operator+=(const Vec2 &other);
        Vec2& operator/=(float num);
        Vec2 operator-(const Vec2 &rhs) const;
        Vec2 operator*(float num) const;
        Vec2 operator/(float num) const;

        Vec2 dir_to(const Vec2 &other) const;
        Vec2 &normalize();
        float dist_to(const Vec2 &other);

        std::tuple<float, float> get_coords();
};

#endif // VEC2_HPP
