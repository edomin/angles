#ifndef DRAW_HPP
#define DRAW_HPP

#include <GLFW/glfw3.h>

class Draw {
    private:
        GLFWwindow* glfw_window;

    public:
        Draw(Window &window);
        ~Draw();

        clear();
        update();
};

#endif // KEYBOARD_HPP
