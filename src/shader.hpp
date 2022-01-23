#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <GL/glew.h>

class Shader {
    private:
        GLuint shader_object;

    public:
        enum class type_t: GLenum {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
        };

        Shader(type_t type, const std::string &source);
        ~Shader();

        GLuint get_shader_object() const;
};

#endif // SHADER_HPP
