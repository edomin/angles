#include "window.hpp"

#include <map>

#include "exception.hpp"

namespace {
    const std::map<int, int> DEFAULT_WINDOW_HINTS = {
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
        {GLFW_DEPTH_BITS,               24},
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
    };
}

Window::Window(unsigned _width, unsigned _height, const std::string &caption)
: glfw_window(nullptr)
, width(_width)
, height(_height) {
    GLenum glew_error;

    for (auto &[key, value] : DEFAULT_WINDOW_HINTS)
        glfwWindowHint(key, value);

    glfw_window = glfwCreateWindow(width, height, caption.c_str(), nullptr,
     nullptr);

    if (!glfw_window)
        ANG_THROW("glfwCreateWindow() failed");

    glfwMakeContextCurrent(glfw_window);

    glewExperimental = true;
    glew_error = glewInit();
    if (glew_error != GLEW_OK)
        ANG_THROW(reinterpret_cast<const char *>(
         glewGetErrorString(glew_error)));

    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
}

Window::~Window() {
    glfwDestroyWindow(glfw_window);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int _width,
 int _height) {
    glViewport(0, 0, _width, _height);
}

void Window::make_current() {
    glfwMakeContextCurrent(glfw_window);
}

void Window::request_close() {
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

bool Window::should_close() {
    return glfwWindowShouldClose(glfw_window);
}

[[gnu::pure]] GLFWwindow *Window::get_glfwwindow() {
    return glfw_window;
}

[[gnu::pure]] unsigned Window::get_width() const {
    return width;
}

[[gnu::pure]] unsigned Window::get_height() const {
    return height;
}
