#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <GL/glew.h>

#include "point.hpp"

class Triangle {
    private:
        Point a;
        Point b;
        Point c;

    public:
        Triangle(const Point &_a, const Point &_b, const Point &_c);
        ~Triangle();
};

#endif // TRIANGLE_HPP
