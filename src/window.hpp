#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow *glfw_window;

    public:
        Window(unsigned width, unsigned height,
         const std::string &caption);
        ~Window();

        void Window::make_current(); // For multiple windows. Not used in current
                                // implementation

        void request_close();
        bool should_close();
        GLFWwindow *get_glfwwindow();
};

#endif // WINDOW_HPP
