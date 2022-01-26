#include "draw.hpp"

#include <iostream> // delete me
#include <limits>
#include <memory>

#include "debug.hpp"
#include "exception.hpp"
#include "shader.hpp"

using namespace std::string_literals;

namespace {
    // I believe my compiler doesn't support constexpr string literals
    const std::string VERTEX_SHADER_SOURCE =
    "#version 330 core\n"
    "attribute vec3 pos;\n"
    "attribute vec2 vert_tex_coord;\n"
    "out       vec2 frag_tex_coord;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "    frag_tex_coord = vert_tex_coord;\n"
    "}\n"s;
    const std::string FRAGMENT_SHADER_SOURCE =
    "#version 330 core\n"
    "in  vec2 frag_tex_coord;\n"
    "out vec4 color;\n"
    "uniform sampler2D in_texture;"
    "void main() {\n"
    "    color = texture(in_texture, frag_tex_coord);\n"
    "}\n"s;

    const size_t      VBO_COMPONENTS_PER_VERTEX      = 5;
    const std::string ATTR_POS_NAME                  = "pos"s;
    const size_t      ATTR_POS_COMPONENTS_COUNT      = 3;
    const size_t      ATTR_POS_OFFSET                = 0;
    const std::string ATTR_TEXTCOORD_NAME            = "vert_tex_coord"s;
    const size_t      ATTR_TEXCOORD_COMPONENTS_COUNT = 2;
    const size_t      ATTR_TEXCOORD_OFFSET           = sizeof(float) * ATTR_POS_COMPONENTS_COUNT;
    const float       ABS_Z_MAX                      = std::numeric_limits<uint16_t>::max();
    const GLdouble    DEPTH_RANGE_NEAR_VAL           = 0.0;
    const GLdouble    DEPTH_RANGE_FAR_VAL            = 1.0;
}

Draw::Draw(Window &_window)
: window(&_window)
, vbo(VBO_COMPONENTS_PER_VERTEX)
, pos_attr_arr()
, tex_coord_attr_arr()
, shader_program()
, draw_queue()
, vertices_data()
, batches_data() {
    std::unique_ptr<Shader> vertex_shader = std::make_unique<Shader>(
     Shader::type_t::VERTEX, VERTEX_SHADER_SOURCE);
    std::unique_ptr<Shader> fragment_shader = std::make_unique<Shader>(
     Shader::type_t::FRAGMENT, FRAGMENT_SHADER_SOURCE);

    shader_program = std::make_unique<ShaderProgram>(*vertex_shader,
     *fragment_shader);
    pos_attr_arr = std::make_unique<VertAttrArr>(vbo, *shader_program,
     ATTR_POS_NAME, ATTR_POS_COMPONENTS_COUNT, ATTR_POS_OFFSET);
    tex_coord_attr_arr = std::make_unique<VertAttrArr>(vbo, *shader_program,
     ATTR_TEXTCOORD_NAME, ATTR_TEXCOORD_COMPONENTS_COUNT, ATTR_TEXCOORD_OFFSET);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthRange(DEPTH_RANGE_NEAR_VAL, DEPTH_RANGE_FAR_VAL);
    glClearDepth(DEPTH_RANGE_FAR_VAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Draw::~Draw() {}

void Draw::add_one_vertex_data(float pos_x, float pos_y, float pos_z, float u,
 float v) {
    vertices_data.push_back(pos_x);
    vertices_data.push_back(pos_y);
    vertices_data.push_back(pos_z);
    vertices_data.push_back(u);
    vertices_data.push_back(v);
}

void Draw::update_vertices_data() {
    const Texture *current_texture = nullptr;
    size_t         first_vertex_index = 0;
    size_t         vertex_index = 0;
    float          window_width;
    float          window_height;

    vertices_data.clear();
    batches_data.clear();

    if (draw_queue.size() == 0)
        return;

    window_width = static_cast<float>(window->get_width());
    window_height = static_cast<float>(window->get_height());

    for (auto &[sprite, outrect] : draw_queue) {
        auto           [x, y, z, hscale, vscale] = outrect;
        const Texture *texture = sprite->get_spritesheet()->get_texture();
        float clip_width = static_cast<float>(
         sprite->get_spritesheet()->get_clip_width());
        float clip_height = static_cast<float>(
         sprite->get_spritesheet()->get_clip_height());
        float pos_upper_left_x = x / window_width - 1.0f;
        float pos_upper_left_y = 1.0f - y / window_height;
        float pos_upper_right_x = (x + clip_width * hscale) / window_width
         - 1.0f;
        float pos_upper_right_y = pos_upper_left_y;
        float pos_lower_left_x = pos_upper_left_x;
        float pos_lower_left_y = 1.0f - (y + clip_height * vscale)
         / window_height;
        float pos_lower_right_x = pos_upper_right_x;
        float pos_lower_right_y = pos_lower_left_y;
        float pos_z = z / ABS_Z_MAX + 0.5f;

        if (!current_texture)
            current_texture = texture;

        if (texture != current_texture) {
            BatchData batch_data(*current_texture, first_vertex_index,
             vertex_index - first_vertex_index);

            batches_data.push_back(batch_data);
            first_vertex_index = vertex_index;
            current_texture = texture;
        }

        add_one_vertex_data(pos_upper_left_x, pos_upper_left_y, pos_z,
         sprite->get_upper_left_u(), sprite->get_upper_left_v());
        add_one_vertex_data(pos_upper_right_x, pos_upper_right_y,pos_z,
         sprite->get_upper_right_u(), sprite->get_upper_right_v());
        add_one_vertex_data(pos_lower_left_x, pos_lower_left_y,pos_z,
         sprite->get_lower_left_u(), sprite->get_lower_left_v());
        add_one_vertex_data(pos_upper_right_x, pos_upper_right_y,pos_z,
         sprite->get_upper_right_u(), sprite->get_upper_right_v());
        add_one_vertex_data(pos_lower_left_x, pos_lower_left_y,pos_z,
         sprite->get_lower_left_u(), sprite->get_lower_left_v());
        add_one_vertex_data(pos_lower_right_x, pos_lower_right_y,pos_z,
         sprite->get_lower_right_u(), sprite->get_lower_right_v());

        vertex_index += 6;
    }
    BatchData batch_data(*current_texture, first_vertex_index,
     vertex_index - first_vertex_index);

    batches_data.push_back(batch_data);
}

void Draw::put_sprite(const Sprite &sprite, float x, float y, float z,
 float hscale, float vscale) {
    if (std::abs(vscale) <= std::abs(std::numeric_limits<float>::epsilon()))
        vscale = hscale;
    draw_queue.insert({&sprite, {x, y, z, hscale, vscale}});
}

void Draw::update() {
    GLenum error;

    update_vertices_data();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_program->use();
    vbo.bind();
    vbo.set_vertices(vertices_data.data(),
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
    vbo.unbind();
    shader_program->unuse();

    glfwSwapBuffers(window->get_glfwwindow());

    draw_queue.clear();
}
