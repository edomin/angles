#ifndef COLOR_HPP
#define COLOR_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Color {
    private:
        float r;
        float g;
        float b;
        float a;

    public:
        Color(uint32_t rgba);
        ~Color();

        float get_r() const;
        float get_g() const;
        float get_b() const;
        float get_a() const;
};

#endif // COLOR_HPP
