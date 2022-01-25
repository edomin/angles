#include "draw.hpp"

#include <iostream> // delete me

#include "exception.hpp"

Draw::Draw(Window &_window, Vbo &_vbo,
 const VertAttrArr &_pos_attr_arr, const VertAttrArr &_tex_coord_attr_arr,
 const ShaderProgram &_shader_program)
: window(&_window)
, vbo(&_vbo)
, pos_attr_arr(&_pos_attr_arr)
, tex_coord_attr_arr(&_tex_coord_attr_arr)
, shader_program(&_shader_program)
, draw_queue()
, vertices_data()
, batches_data() {}

Draw::~Draw() {}

void Draw::add_one_vertex_data(float pos_x, float pos_y, float u, float v) {
    vertices_data.push_back(pos_x);
    vertices_data.push_back(pos_y);
    vertices_data.push_back(0.0f);
    vertices_data.push_back(u);
    vertices_data.push_back(v);
}

void Draw::update_vertices_data() {
    const Texture *current_texture = nullptr;
    size_t         first_vertex_index = 0;
    size_t         vertex_index = 0;
    float          window_width = static_cast<float>(window->get_width());
    float          window_height = static_cast<float>(window->get_height());

    vertices_data.clear();
    batches_data.clear();

    for (auto &[sprite, coords] : draw_queue) {
        const Texture *texture = sprite->get_spritesheet()->get_texture();
        float clip_width = static_cast<float>(
         sprite->get_spritesheet()->get_clip_width());
        float clip_height = static_cast<float>(
         sprite->get_spritesheet()->get_clip_height());
        float pos_upper_left_x = coords.first / window_width - 1.0f;
        float pos_upper_left_y = 1.0f - coords.second / window_height;
        float pos_upper_right_x = (coords.first + clip_width) / window_width
         - 1.0f;
        float pos_upper_right_y = 1.0f - coords.second / window_height;
        float pos_lower_left_x = coords.first / window_width - 1.0f;
        float pos_lower_left_y = 1.0f - (coords.second + clip_height)
         / window_height;
        float pos_lower_right_x = (coords.first + clip_width) / window_width
         - 1.0f;
        float pos_lower_right_y = 1.0f - (coords.second + clip_height)
         / window_height;

        if (!current_texture)
            current_texture = texture;

        if (texture != current_texture) {
            BatchData batch_data(*current_texture, first_vertex_index,
             vertex_index - first_vertex_index);

            batches_data.push_back(batch_data);
            first_vertex_index = vertex_index;
            current_texture = texture;
        }

        add_one_vertex_data(pos_upper_left_x, pos_upper_left_y,
         sprite->get_upper_left_u(), sprite->get_upper_left_v());
        add_one_vertex_data(pos_upper_right_x, pos_upper_right_y,
         sprite->get_upper_right_u(), sprite->get_upper_right_v());
        add_one_vertex_data(pos_lower_left_x, pos_lower_left_y,
         sprite->get_lower_left_u(), sprite->get_lower_left_v());
        add_one_vertex_data(pos_upper_right_x, pos_upper_right_y,
         sprite->get_upper_right_u(), sprite->get_upper_right_v());
        add_one_vertex_data(pos_lower_left_x, pos_lower_left_y,
         sprite->get_lower_left_u(), sprite->get_lower_left_v());
        add_one_vertex_data(pos_lower_right_x, pos_lower_right_y,
         sprite->get_lower_right_u(), sprite->get_lower_right_v());

        vertex_index += 6;
    }
    BatchData batch_data(*current_texture, first_vertex_index,
     vertex_index - first_vertex_index);

    batches_data.push_back(batch_data);
}

void Draw::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::fill(const Color &color) {
    glClearColor(color.get_r(), color.get_g(), color.get_b(), color.get_a());
}

void Draw::put_sprite(const Sprite &sprite, float x, float y) {
    draw_queue.insert({&sprite, {x, y}});
}

void Draw::update() {
    GLenum error;

    update_vertices_data();

    glClear(GL_COLOR_BUFFER_BIT);

    shader_program->use();
    vbo->bind();
    vbo->set_vertices(vertices_data.data(),
     sizeof(float) * vertices_data.size());
    for (size_t i = 0; i < batches_data.size(); i++) {
        pos_attr_arr->enable();
        tex_coord_attr_arr->enable();

        batches_data[i].get_texture()->bind();

        glDrawArrays(GL_TRIANGLES, batches_data[i].get_first_vertex_index(),
         batches_data[i].get_vertices_count());

        error = glGetError();
        if (error != GL_NO_ERROR)
            ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error)));

        pos_attr_arr->disable();
        tex_coord_attr_arr->disable();
    }
    vbo->unbind();
    shader_program->unuse();

    glfwSwapBuffers(window->get_glfwwindow());

    draw_queue.clear();
}
