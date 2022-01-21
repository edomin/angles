#include "draw.hpp"

Draw::Draw(Window &window)
: glfw_window(window.get_glfwwindow()) {

}

Draw::~Draw() {

}

Draw::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

Draw::update() {
    glfwSwapBuffers(glfw_window);
}
