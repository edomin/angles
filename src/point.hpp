#ifndef POINT_HPP
#define POINT_HPP

#include <GL/glew.h>

class Point {
    private:
        float x;
        float y;
        float z;

    public:
        Point(float _x, float _y, float _z);
        ~Point();
};

#endif // POINT_HPP
