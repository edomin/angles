#include "vertex_attribute_array.hpp"

namespace {
    const GLuint DEFAULT_INDEX              = 0;
    const GLint  DEFAULT_VERTEX_ATTRIB_SIZE = 3;
}

VertAttrArr::VertAttrArr(const ShaderProgram &_shader_program,
 const std::string &attribute_name, size_t components_count, size_t offset)
: attribute_location()
, shader_program(&_shader_program) {
    attribute_location = glGetAttribLocation(
     shader_program->get_program_object(), attribute_name.c_str());

    glEnableVertexAttribArray(attribute_location);
    glVertexAttribPointer(attribute_location, components_count, GL_FLOAT,
     GL_FALSE, sizeof(float), reinterpret_cast<void *>(offset));
    glDisableVertexAttribArray(DEFAULT_INDEX);
}

VertAttrArr::~VertAttrArr() {

}

void VertAttrArr::enable() const {
    glEnableVertexAttribArray(attribute_location);
}

void VertAttrArr::disable() const {
    glDisableVertexAttribArray(attribute_location);
}
