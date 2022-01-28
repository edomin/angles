#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

class Mouse {
    private:
        GLFWwindow* glfw_window;

    public:
        enum class button_t: int {
            LEFT = GLFW_MOUSE_BUTTON_LEFT,
            RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
            MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        };

        Mouse(Window &window);
        ~Mouse();

        std::tuple<float, float> get_cursor_pos();
        bool button_down(button_t button);
        bool button_up(button_t button);
};

#endif // MOUSE_HPP
