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

void Mouse::update() {
    int glfw_button_left = static_cast<std::underlying_type_t<button_t>>(
     button_t::LEFT);
    int glfw_button_right = static_cast<std::underlying_type_t<button_t>>(
     button_t::RIGHT);
    int glfw_button_middle = static_cast<std::underlying_type_t<button_t>>(
     button_t::MIDDLE);
    int glfw_left_state = glfwGetMouseButton(glfw_window, glfw_button_left);
    int glfw_right_state = glfwGetMouseButton(glfw_window, glfw_button_right);
    int glfw_middle_state = glfwGetMouseButton(glfw_window, glfw_button_middle);

    prev_button_state = button_state;
    button_state[button_t::LEFT] = glfw_left_state == GLFW_PRESS;
    button_state[button_t::RIGHT] = glfw_right_state == GLFW_PRESS;
    button_state[button_t::MIDDLE] = glfw_middle_state == GLFW_PRESS;
}

Vec2 Mouse::get_cursor_pos() {
    double mouse_x;
    double mouse_y;

    glfwGetCursorPos(glfw_window, &mouse_x, &mouse_y);

    return Vec2{static_cast<float>(mouse_x), static_cast<float>(mouse_y)};
}

bool Mouse::button_down(button_t button) {
    return button_state[button] && !prev_button_state[button];
}

bool Mouse::button_up(button_t button) {
    return !button_state[button] && prev_button_state[button];
}

bool Mouse::button_hold(button_t button) {
    return button_state[button];
}

bool Mouse::left_button_down() {
    return button_down(button_t::LEFT);
}

bool Mouse::left_button_up() {
    return button_up(button_t::LEFT);
}

bool Mouse::left_button_hold() {
    return button_hold(button_t::LEFT);
}

bool Mouse::right_button_down() {
    return button_down(button_t::RIGHT);
}

bool Mouse::right_button_up() {
    return button_up(button_t::RIGHT);
}

bool Mouse::right_button_hold() {
    return button_hold(button_t::RIGHT);
}

bool Mouse::middle_button_down() {
    return button_down(button_t::MIDDLE);
}

bool Mouse::middle_button_up() {
    return button_up(button_t::MIDDLE);
}

bool Mouse::middle_button_hold() {
    return button_hold(button_t::MIDDLE);
}
