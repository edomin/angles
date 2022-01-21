#include "keyboard.hpp"

#include <vector>
#include <utility>

// We use std::vector because it can be constexpr
constexpr std::vector<std::pair<int, int>> DEFAULT_KEYBOARD_INPUT_MODES = {
    {GLFW_STICKY_KEYS,   GLFW_TRUE},
    {GLFW_LOCK_KEY_MODS, GLFW_FALSE},
}

Keyboard::Keyboard(Window &window)
: glfw_window(window.get_glfwwindow())
, keys() {
    for (std::pair<int, int> mode : DEFAULT_KEYBOARD_INPUT_MODES)
        glfwSetInputMode(glfw_window, mode.first, mode.second);


}

Keyboard::~Keyboard() {

}

bool Keyboard::register_key(int key, int glfw_key) {
    auto [_, success] = insert({key, glfw_key});

    return success;
}

bool Keyboard::key_down(int key) {
    if keys.contains(key)
        return glfwGetKey(glfw_window, keys.at(key)) == GLFW_PRESS;

    return false;
}
