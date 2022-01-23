#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <GLFW/glfw3.h>

class Mouse {
    private:
        GLFWwindow* glfw_window;

    public:
        enum class button_t: int {
            LEFT = GLFW_MOUSE_BUTTON_LEFT,
            RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
            MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        }

        Mouse(Window &window);
        ~Mouse();

        bool button_down(button_t button);
};

#endif // MOUSE_HPP
