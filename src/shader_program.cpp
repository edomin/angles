#include "shader_program.hpp"

#include "exception.hpp"

namespace {
    const GLsizei LOG_SIZE = 1024;
}

ShaderProgram::ShaderProgram(const Shader &vertex_shader,
 const Shader &fragment_shader)
: program_object(glCreateProgram()) {
    GLint  compiled;
    GLchar log[LOG_SIZE];

    glAttachShader(program_object, vertex_shader.get_shader_object());
    glAttachShader(program_object, fragment_shader.get_shader_object());
    glLinkProgram(program_object);

    glGetProgramiv(program_object, GL_LINK_STATUS, &compiled);
    if(!compiled) {
        glGetProgramInfoLog(program_object, LOG_SIZE, nullptr, log);
        ANG_THROW(log);
    }
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::use() const {
    glUseProgram(program_object);
}

void ShaderProgram::unuse() const {
    glUseProgram(0);
}

GLuint ShaderProgram::get_program_object() const {
    return program_object;
}
