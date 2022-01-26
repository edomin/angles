#include <memory>
#include <string>

#include "app.hpp"
#include "draw.hpp"
#include "iimg.hpp"
#include "res_keeper.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "timer.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

#include "debug.hpp" //delete me

using namespace std::string_literals;

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

int main(int argc, char **argv) {
    App           app;
    Timer         timer;
    Window        window(800, 600, "angles"s);
    ResKeeper     resources;
    [[maybe_unused]]Vao vao;
    Shader        vertex_shader(Shader::type_t::VERTEX, VERTEX_SHADER_SOURCE);
    Shader        fragment_shader(Shader::type_t::FRAGMENT, FRAGMENT_SHADER_SOURCE);
    ShaderProgram shader_program(vertex_shader, fragment_shader);
    Vbo           vbo;
    VertAttrArr   pos_attr_arr(vbo, shader_program, "pos"s, 3, 0);
    VertAttrArr   tex_coord_attr_arr(vbo, shader_program, "vert_tex_coord"s, 2, sizeof(float) * 3);
    Draw          draw(window, vbo, pos_attr_arr, tex_coord_attr_arr, shader_program);

    while (!window.should_close()) {
        [[maybe_unused]] double delta_time = timer.update();

        // draw.put_sprite(spr_floor, 20.0f, 32.0f, 300.0f, 8.0f);
        // draw.put_sprite(spr_boy, 500.0f, 32.0f, 200.0f, 8.0f);

        draw.update();
        app.update();
    }

    return 0;
}
