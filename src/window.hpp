#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow *glfw_window;

        // Not used in current implementation
        static void framebuffer_size_callback(GLFWwindow* window, int width,
         int height);

    public:
        Window(unsigned width, unsigned height, const std::string &caption);
        ~Window();

        // For multiple windows. Not used in current implementation
        void make_current();

        void request_close();
        bool should_close();
        GLFWwindow *get_glfwwindow();
};

#endif // WINDOW_HPP
