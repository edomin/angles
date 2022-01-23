#ifndef DRAW_HPP
#define DRAW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "color.hpp"
#include "vbo.hpp"
#include "shader_program.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

class Draw {
    private:
        GLFWwindow          *glfw_window;
        Vbo                 *position_buffer_object;
        const VertAttrArr   *vert_attr_arr;
        const ShaderProgram *shader_program;

    public:
        Draw(Window &window, Vbo &_position_buffer_object,
         const VertAttrArr &_vert_attr_arr,
         const ShaderProgram &_shader_program);
        ~Draw();

        void clear();
        void fill(const Color &color);
        void update();
};

#endif // KEYBOARD_HPP
