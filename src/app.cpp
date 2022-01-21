#include "app.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

App::App() {
    glewExperimental = true;

    if (!glfwInit())
        /* throw */

    if (glewInit() != GLEW_OK)
        /* throw */

}

App::~App() {
    glfwTerminate();
}

App::update() {
    glfwPollEvents();
}
