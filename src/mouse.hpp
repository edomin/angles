#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vec2.hpp"
#include "window.hpp"

class Mouse {
    public:
        enum class button_t: int {
            LEFT = GLFW_MOUSE_BUTTON_LEFT,
            RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
            MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        };

    private:
        GLFWwindow* glfw_window;

        std::map<button_t, bool> prev_button_state;
        std::map<button_t, bool> button_state;

        // static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    public:
        Mouse(Window &window);
        ~Mouse();

        void update();
        Vec2 get_cursor_pos();
        bool button_down(button_t button);
        bool button_up(button_t button);
        bool button_hold(button_t button);
};

#endif // MOUSE_HPP
