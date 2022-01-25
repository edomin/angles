#include "draw.hpp"

#include <iostream> // delete me

#include "exception.hpp"

Draw::Draw(Window &_window, Vbo &_position_buffer_object,
 const VertAttrArr &_pos_attr_arr, const VertAttrArr &_tex_coord_attr_arr,
 const ShaderProgram &_shader_program)
: window(&_window)
, position_buffer_object(&_position_buffer_object)
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
    // ptrdiff_t vbo_offset = 0;
    ptrdiff_t first_vertex_index = 0;
    size_t    vertex_index = 0;
    float     window_width = static_cast<float>(window->get_width());
    float     window_height = static_cast<float>(window->get_height());

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
        float pos_lower_left_y = 1.0f - (coords.second + clip_height) / window_height;
        float pos_lower_right_x = (coords.first + clip_width) / window_width
         - 1.0f;
        float pos_lower_right_y = 1.0f - (coords.second + clip_height) / window_height;

        if (!current_texture)
            current_texture = texture;

        if (texture != current_texture) {
            // std::cout << "current_texture: " << current_texture << std::endl;
            // std::cout << "texture: " << texture << std::endl;

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

    // std::cout << "batches_data.size(): " << batches_data.size() << std::endl;
    // std::cout << "batches_data[0].get_vertices_count(): " << batches_data[0].get_vertices_count() << std::endl;
    // std::cout << "batches_data[0].get_vertices_size(): " << batches_data[0].get_vertices_size() << std::endl;
    // std::cout << "batches_data[0].get_vbo_offset(): " << batches_data[0].get_vbo_offset() << std::endl;
    // std::cout << "batches_data[0].get_texture(): " << batches_data[0].get_texture() << std::endl;
    // std::cout << "batches_data[1].get_vertices_count(): " << batches_data[1].get_vertices_count() << std::endl;
    // std::cout << "batches_data[1].get_vertices_size(): " << batches_data[1].get_vertices_size() << std::endl;
    // std::cout << "batches_data[1].get_vbo_offset(): " << batches_data[1].get_vbo_offset() << std::endl;
    // std::cout << "batches_data[1].get_texture(): " << batches_data[1].get_texture() << std::endl;

    // for (size_t i = 0; i < vertices_data.size(); i += 5) {
    //     std::cout << "vertex " << i << " x: " << vertices_data[i + 0] << std::endl;
    //     std::cout << "vertex " << i << " y: " << vertices_data[i + 1] << std::endl;
    //     std::cout << "vertex " << i << " z: " << vertices_data[i + 2] << std::endl;
    //     std::cout << "vertex " << i << " u: " << vertices_data[i + 3] << std::endl;
    //     std::cout << "vertex " << i << " v: " << vertices_data[i + 4] << std::endl;
    // }
    // for (size_t i = 0; i < vertices_data.size(); i++) {
    //     std::cout << "vertices_data[" << i << "]: " << vertices_data[i] << std::endl;
    // }

    // std::cout << "vertices_data[0]: " << vertices_data[0] << std::endl;
    // std::cout << "vertices_data[1]: " << vertices_data[1] << std::endl;
    // std::cout << "vertices_data[8]: " << vertices_data[8] << std::endl;
    // std::cout << "vertices_data[30]: " << vertices_data[30] << std::endl;
    // std::cout << "vertices_data[31]: " << vertices_data[31] << std::endl;
    // std::cout << "vertices_data[38]: " << vertices_data[38] << std::endl;
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

    // float vertices[] = {
    //     -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
    //     1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    // };
    update_vertices_data();
    // std::cout << vertices_data.size() << std::endl;

    glClear(GL_COLOR_BUFFER_BIT);

    // shader_program->use();
    // position_buffer_object->bind();
    // position_buffer_object->set_vertices(vertices, sizeof(float) * 15);
    // pos_attr_arr->enable();
    // tex_coord_attr_arr->enable();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // pos_attr_arr->disable();
    // tex_coord_attr_arr->disable();
    // position_buffer_object->unbind();

    shader_program->use();
    // std::cout << batches_data.size() << std::endl;
    position_buffer_object->bind();
    position_buffer_object->set_vertices(vertices_data.data(),
     sizeof(float) * vertices_data.size());
    for (size_t i = 0; i < batches_data.size(); i++) {
        // position_buffer_object->bind();
        // position_buffer_object->set_vertices(
        //  vertices_data.data() + batches_data[i].get_vbo_offset(),
        //  batches_data[i].get_vertices_size());

        // position_buffer_object->set_vertices(
        //  vertices_data.data(),
        //  sizeof(float) * 30);
        pos_attr_arr->enable();
        tex_coord_attr_arr->enable();

        // std::cout << batches_data[i].get_vbo_offset() << std::endl;
        // std::cout << batches_data[i].get_vertices_count() << std::endl;

        // std::cout << vertices_data[0] << std::endl;
        // std::cout << vertices_data[1] << std::endl;
        // std::cout << vertices_data[5] << std::endl;
        // std::cout << vertices_data[6] << std::endl;
        // std::cout << vertices_data[10] << std::endl;
        // std::cout << vertices_data[11] << std::endl;
        // std::cout << vertices_data[15] << std::endl;
        // std::cout << vertices_data[16] << std::endl;
        // std::cout << vertices_data[20] << std::endl;
        // std::cout << vertices_data[21] << std::endl;
        // std::cout << vertices_data[25] << std::endl;
        // std::cout << vertices_data[26] << std::endl;
        // std::cout << std::endl;

        batches_data[i].get_texture()->bind();

        glDrawArrays(GL_TRIANGLES, batches_data[i].get_first_vertex_index(), batches_data[i].get_vertices_count());

        error = glGetError();
        if (error != GL_NO_ERROR)
            ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error)));

        pos_attr_arr->disable();
        tex_coord_attr_arr->disable();
    }
    position_buffer_object->unbind();
    shader_program->unuse();

    glfwSwapBuffers(window->get_glfwwindow());

    draw_queue.clear();
}
