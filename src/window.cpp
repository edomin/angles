#include "window.hpp"

#include <vector>
#include <utility>

// Some of this hints must be in external config file
// We use std::vector because it can be constexpr
constexpr std::vector<std::pair<int, int>> DEFAULT_WINDOW_HINTS = {
    {GLFW_RESIZABLE,                GLFW_FALSE},
    {GLFW_VISIBLE,                  GLFW_TRUE},
    {GLFW_DECORATED,                GLFW_TRUE},
    {GLFW_FOCUSED,                  GLFW_TRUE},
    {GLFW_AUTO_ICONIFY,             GLFW_FALSE},
    {GLFW_FLOATING,                 GLFW_FALSE},
    {GLFW_MAXIMIZED,                GLFW_FALSE},
    {GLFW_CENTER_CURSOR,            GLFW_TRUE},
    {GLFW_TRANSPARENT_FRAMEBUFFER,  GLFW_FALSE},
    {GLFW_FOCUS_ON_SHOW,            GLFW_TRUE},
    {GLFW_SCALE_TO_MONITOR,         GLFW_FALSE},
    {GLFW_RED_BITS,                 8},
    {GLFW_GREEN_BITS,               8},
    {GLFW_BLUE_BITS,                8},
    {GLFW_ALPHA_BITS,               8},
    {GLFW_DEPTH_BITS,               GLFW_DONT_CARE},
    {GLFW_STENCIL_BITS,             GLFW_DONT_CARE},
    {GLFW_ACCUM_RED_BITS,           GLFW_DONT_CARE},
    {GLFW_ACCUM_GREEN_BITS,         GLFW_DONT_CARE},
    {GLFW_ACCUM_BLUE_BITS,          GLFW_DONT_CARE},
    {GLFW_ACCUM_ALPHA_BITS,         GLFW_DONT_CARE},
    {GLFW_AUX_BUFFERS,              GLFW_DONT_CARE},
    {GLFW_STEREO,                   GLFW_FALSE},
    {GLFW_SAMPLES,                  0},
    {GLFW_SRGB_CAPABLE,             GLFW_TRUE},
    {GLFW_DOUBLEBUFFER,             GLFW_TRUE},
    {GLFW_REFRESH_RATE,             60},
    {GLFW_CLIENT_API,               GLFW_OPENGL_API},
    // GLFW_CONTEXT_CREATION_API
    {GLFW_CONTEXT_VERSION_MAJOR,    3},
    {GLFW_CONTEXT_VERSION_MINOR,    3},
    {GLFW_OPENGL_FORWARD_COMPAT,    GLFW_TRUE},
    {GLFW_OPENGL_DEBUG_CONTEXT,     GLFW_TRUE},
    {GLFW_OPENGL_PROFILE,           GLFW_OPENGL_CORE_PROFILE},
    {GLFW_CONTEXT_ROBUSTNESS,       GLFW_LOSE_CONTEXT_ON_RESET},
    {GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH},
    {GLFW_CONTEXT_NO_ERROR,         GLFW_FALSE},
    {GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE},
    // GLFW_COCOA_FRAME_NAME
    {GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_FALSE},
    // GLFW_X11_CLASS_NAME
    // GLFW_X11_INSTANCE_NAME
}

Window::Window(unsigned width, unsigned height,
 const std::string &caption)
: glfw_window(nullptr) {
    for (std::pair<int, int> hint : DEFAULT_WINDOW_HINTS)
        glfwWindowHint(hint.first, hint.second);

    glfw_window = glfwCreateWindow(width, height, caption, nullptr, nullptr);

    if (!glfw_window)
        /* throw */

    glfwMakeContextCurrent(glfw_window);
}

Window::~Window() {
    glfwDestroyWindow(glfw_window);
}

void Window::make_current() {
    glfwMakeContextCurrent(glfw_window);
}

void Window::request_close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::should_close() {
    return glfwWindowShouldClose(window) == 0;
}

GLFWwindow *Window::get_glfwwindow() {
    return glfw_window;
}