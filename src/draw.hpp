#ifndef DRAW_HPP
#define DRAW_HPP

// #include <unordered_map>
#include <memory>
#include <tuple>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "batch_data.hpp"
#include "vbo.hpp"
#include "shader_program.hpp"
#include "sprite.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

class Draw {
    private:
        // typedef std::pair<float, float> coords_t;
        typedef std::tuple<
            const Sprite *,
            float, // x - 0..window_width
            float, // y - 0..window_height
            float, // z - -int32max..+int32max
            float, // hscale - any
            float  // vscale - any
        > outdata_t;
        typedef std::vector<outdata_t> draw_queue_t;

        static constexpr float         SCALE_NO             = 1.0f;
        static constexpr float         SCALE_SAME_AS_HSCALE = 0.0f;

        Window                        *window;
        Vbo                            vbo;
        std::unique_ptr<VertAttrArr>   pos_attr_arr;
        std::unique_ptr<VertAttrArr>   tex_coord_attr_arr;
        std::unique_ptr<ShaderProgram> shader_program;

        draw_queue_t                   draw_queue;
        std::vector<float>             vertices_data;
        std::vector<BatchData>         batches_data;

        void add_one_vertex_data(float pos_x, float pos_y, float pos_z, float u,
         float v);
        void update_vertices_data();

    public:
        Draw(Window &_window);
        ~Draw();

        // void fill(const Color &color);
        void put_sprite(const Sprite &sprite, float x, float y, float z,
         float hscale = SCALE_NO, float vscale = SCALE_SAME_AS_HSCALE);
        void update();
};

#endif // KEYBOARD_HPP
