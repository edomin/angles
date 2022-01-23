#include "draw.hpp"

#include "exception.hpp"

Draw::Draw(Window &window, Vbo &_position_buffer_object,
 const VertAttrArr &_vert_attr_arr, const ShaderProgram &_shader_program)
: glfw_window(window.get_glfwwindow())
, position_buffer_object(&_position_buffer_object)
, vert_attr_arr(&_vert_attr_arr)
, shader_program(&_shader_program) {}

Draw::~Draw() {

}

void Draw::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::fill(const Color &color) {
    glClearColor(color.get_r(), color.get_g(), color.get_b(), color.get_a());
}

void Draw::update() {
    GLenum error;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glClear(GL_COLOR_BUFFER_BIT);

    shader_program->use();

    position_buffer_object->bind();
    position_buffer_object->set_vertices(vertices, sizeof(float) * 9);
    vert_attr_arr->enable();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    error = glGetError();
    if (error != GL_NO_ERROR)
        ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error)));

    vert_attr_arr->disable();
    position_buffer_object->unbind();
    shader_program->unuse();

    glfwSwapBuffers(glfw_window);
}
