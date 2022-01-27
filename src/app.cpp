#include "app.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception.hpp"

App::App() {
    if (!glfwInit())
        ANG_THROW("glfwInit() failed");
}

App::~App() {
    glfwTerminate();
}

void App::update() const {
    glfwPollEvents();
}
