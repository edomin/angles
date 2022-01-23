#include "mouse.hpp"

#include <map>

namespace {
    const std::map<int, int> DEFAULT_MOUSE_INPUT_MODES = {
        {GLFW_CURSOR,               GLFW_CURSOR_NORMAL},
        {GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE},
        {GLFW_RAW_MOUSE_MOTION,     GLFW_FALSE},
    };
}

Mouse::Mouse(Window &window)
: glfw_window(window.get_glfwwindow()) {
    for (auto &[key, value] : DEFAULT_MOUSE_INPUT_MODES)
        glfwSetInputMode(glfw_window, key, value);
}

Mouse::~Mouse() {

}

bool Mouse::button_down(button_t button) {
    int glfw_button = static_cast<std::underlying_type_t<button_t>>(button);

    return glfwGetMouseButton(glfw_window, glfw_button) == GLFW_PRESS;
}
