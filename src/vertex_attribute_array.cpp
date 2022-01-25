#include "vertex_attribute_array.hpp"

#include <iostream> // delete me
#include "debug.hpp" // delete me

VertAttrArr::VertAttrArr(const Vbo &vbo, const ShaderProgram &_shader_program,
 const std::string &attribute_name, size_t components_count,
 size_t offset)
: attribute_location()
, shader_program(&_shader_program) {
    GLenum error;

    attribute_location = glGetAttribLocation(
     shader_program->get_program_object(), attribute_name.c_str());

    glEnableVertexAttribArray(attribute_location);
    vbo.bind();
    glVertexAttribPointer(attribute_location, components_count, GL_FLOAT,
     GL_FALSE, sizeof(float) * 5, reinterpret_cast<void *>(offset));

    error = glGetError();
    if (error != GL_NO_ERROR)
        ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error)));

    vbo.unbind();
    glDisableVertexAttribArray(attribute_location);
}

VertAttrArr::~VertAttrArr() {

}

void VertAttrArr::enable() const {
    glEnableVertexAttribArray(attribute_location);
}

void VertAttrArr::disable() const {
    glDisableVertexAttribArray(attribute_location);
}
