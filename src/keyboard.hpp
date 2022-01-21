#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <map>

#include <GLFW/glfw3.h>

class Keyboard {
    private:
        GLFWwindow*                glfw_window;
        std::map<int, int> keys;

    public:
        Keyboard(Window &window);
        ~Keyboard();

        bool register_key(int key, int glfw_key);
        bool key_down(int key);
};

#endif // KEYBOARD_HPP
