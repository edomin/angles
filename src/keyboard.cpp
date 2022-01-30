#include "keyboard.hpp"

#include <map>

namespace {
    const std::map<int, int> DEFAULT_KEYBOARD_INPUT_MODES = {
        {GLFW_STICKY_KEYS,   GLFW_TRUE},
        {GLFW_LOCK_KEY_MODS, GLFW_FALSE},
    };
}

Keyboard::Keyboard(Window &window)
: glfw_window(window.get_glfwwindow())
, keys() {
    for (auto &[key, value] : DEFAULT_KEYBOARD_INPUT_MODES)
        glfwSetInputMode(glfw_window, key, value);
}

Keyboard::~Keyboard() {

}

bool Keyboard::register_key(int key, int glfw_key) {
    auto [_, success] = keys.insert({key, glfw_key});

    return success;
}

bool Keyboard::key_down(int key) {
    if (keys.contains(key))
        return glfwGetKey(glfw_window, keys.at(key)) == GLFW_PRESS;

    return false;
}
