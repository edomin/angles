#include "timer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Timer::Timer()
: last_time(0.0) {
    glfwSetTime(0.0);
}

Timer::~Timer() {}

double Timer::update() {
    double new_time = glfwGetTime();
    double diff = new_time - last_time;

    last_time = new_time;

    return diff;
}
