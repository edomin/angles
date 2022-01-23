#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>

#include <GL/glew.h>

#include "shader.hpp"

class ShaderProgram {
    private:
        GLuint program_object;

    public:
        ShaderProgram(const Shader &vertex_shader,
         const Shader &fragment_shader);
        ~ShaderProgram();

        void use() const;
        void unuse() const;

        GLuint get_program_object() const;
};

#endif // SHADER_PROGRAM_HPP
