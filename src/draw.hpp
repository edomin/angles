#ifndef DRAW_HPP
#define DRAW_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "batch_data.hpp"
#include "color.hpp"
#include "vbo.hpp"
#include "shader_program.hpp"
#include "sprite.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

class Draw {
    private:
        typedef std::pair<float, float> coords_t;
        typedef std::multimap<const Sprite *, coords_t> draw_queue_t;

        Window                *window;
        // GLFWwindow            *glfw_window;
        Vbo                   *position_buffer_object;
        const VertAttrArr     *pos_attr_arr;
        const VertAttrArr     *tex_coord_attr_arr;
        const ShaderProgram   *shader_program;

        draw_queue_t           draw_queue;
        std::vector<float>     vertices_data;
        std::vector<BatchData> batches_data;

        void add_one_vertex_data(float pos_x, float pos_y, float u, float v);
        void update_vertices_data();

    public:
        Draw(Window &_window, Vbo &_position_buffer_object,
         const VertAttrArr &_pos_attr_arr,
         const VertAttrArr &_tex_coord_attr_arr,
         const ShaderProgram &_shader_program);
        ~Draw();

        void clear();
        void fill(const Color &color);
        void put_sprite(const Sprite &sprite, float x, float y);
        void update();
};

#endif // KEYBOARD_HPP
