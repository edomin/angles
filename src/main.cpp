#include <string>

#include "app.hpp"
#include "draw.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "timer.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex_attribute_array.hpp"
#include "window.hpp"

const std::string VERTEX_SHADER_SOURCE =
"#version 330 core\n"
"attribute vec3 pos;\n"
"void main() {\n"
"    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
"}\n";
const std::string FRAGMENT_SHADER_SOURCE =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

int main(int argc, char **argv) {
    App           app;
    Timer         timer;
    Window        window(800, 600, "angles");
    [[maybe_unused]]Vao vao;
    Shader        vertex_shader(Shader::type_t::VERTEX, VERTEX_SHADER_SOURCE);
    Shader        fragment_shader(Shader::type_t::FRAGMENT, FRAGMENT_SHADER_SOURCE);
    ShaderProgram shader_program(vertex_shader, fragment_shader);
    Vbo           position_buffer_object;
    VertAttrArr   vert_attr_arr(shader_program, "pos", 3, 0);
    Draw          draw(window, position_buffer_object, vert_attr_arr, shader_program);

    while (!window.should_close()) {
        [[maybe_unused]] double delta_time = timer.update();

        draw.update();
        app.update();
    }

    return 0;
}
