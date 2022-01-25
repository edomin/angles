#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow *glfw_window;
        unsigned    width;
        unsigned    height;

        // Not used in current implementation
        static void framebuffer_size_callback(GLFWwindow* window, int _width,
         int _height);

    public:
        Window(unsigned _width, unsigned _height, const std::string &caption);
        ~Window();

        // For multiple windows. Not used in current implementation
        void make_current();

        void request_close();
        bool should_close();
        GLFWwindow *get_glfwwindow();
        unsigned get_width() const;
        unsigned get_height() const;
};

#endif // WINDOW_HPP
