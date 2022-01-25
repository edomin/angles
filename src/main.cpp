#include <memory>
#include <string>

#include "app.hpp"
#include "draw.hpp"
#include "iimg.hpp"
#include "img_characters.hpp"
#include "img_floor.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "sprite.hpp"
#include "spritesheet.hpp"
#include "texture.hpp"
#include "timer.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

#include "debug.hpp" //delete me

const std::string VERTEX_SHADER_SOURCE =
"#version 330 core\n"
"attribute vec3 pos;\n"
"attribute vec2 vert_tex_coord;\n"
"out       vec2 frag_tex_coord;\n"
"void main() {\n"
"    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
"    frag_tex_coord = vert_tex_coord;\n"
"}\n";
const std::string FRAGMENT_SHADER_SOURCE =
"#version 330 core\n"
"in  vec2 frag_tex_coord;\n"
"out vec4 color;\n"
"uniform sampler2D in_texture;"
"void main() {\n"
"    color = texture(in_texture, frag_tex_coord);\n"
"}\n";

int main(int argc, char **argv) {
    App           app;
    Timer         timer;
    Window        window(800, 600, "angles");
    [[maybe_unused]]Vao vao;
    Shader        vertex_shader(Shader::type_t::VERTEX, VERTEX_SHADER_SOURCE);
    Shader        fragment_shader(Shader::type_t::FRAGMENT, FRAGMENT_SHADER_SOURCE);
    ShaderProgram shader_program(vertex_shader, fragment_shader);
    Vbo           vbo;
    VertAttrArr   pos_attr_arr(vbo, shader_program, "pos", 3, 0);
    VertAttrArr   tex_coord_attr_arr(vbo, shader_program, "vert_tex_coord", 2, sizeof(float) * 3);
    Draw          draw(window, vbo, pos_attr_arr, tex_coord_attr_arr, shader_program);

    std::unique_ptr<IImg> img_characters = std::make_unique<ImgCharacters>();
    std::unique_ptr<IImg> img_floor = std::make_unique<ImgFloor>();
    Texture tex_characters(img_characters->get_data(), img_characters->get_width(), img_characters->get_height());
    Texture tex_floor(img_floor->get_data(), img_floor->get_width(), img_floor->get_height());
    Spritesheet sprsh_characters(tex_characters, 16, 16);
    Spritesheet sprsh_floor(tex_floor, 128, 128);
    Sprite spr_boy(sprsh_characters, 0);
    Sprite spr_girl(sprsh_characters, 3);
    Sprite spr_floor(sprsh_floor, 0);

    while (!window.should_close()) {
        [[maybe_unused]] double delta_time = timer.update();

        draw.put_sprite(spr_floor, 20.0f, 32.0f, 300.0f, 0.0f, 0.0f);
        draw.put_sprite(spr_boy, 12.0f, 32.0f, 301.0f, 0.0f, 0.0f);

        draw.update();
        app.update();
    }

    return 0;
}
