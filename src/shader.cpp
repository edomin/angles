#include "shader.hpp"

#include "exception.hpp"

namespace {
    const GLsizei DEFAULT_SOURCES_COUNT = 1;
    const GLsizei LOG_SIZE = 1024;
}

Shader::Shader(type_t type, const std::string &source)
: shader_object(
   glCreateShader(static_cast<std::underlying_type_t<type_t>>(type))
  ) {
    const GLchar *c_source = source.c_str();
    GLint         compiled;
    GLchar        log[LOG_SIZE];

    glShaderSource(shader_object, DEFAULT_SOURCES_COUNT, &c_source, nullptr);
    glCompileShader(shader_object);

    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        glGetShaderInfoLog(shader_object, LOG_SIZE, nullptr, log);
        ANG_THROW(log);
    }
}

Shader::~Shader() {
    glDeleteShader(shader_object);
}

[[gnu::pure]] GLuint Shader::get_shader_object() const {
    return shader_object;
}
