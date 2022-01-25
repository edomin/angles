#ifndef VERTEX_ATTRIBUTE_ARRAY_HPP
#define VERTEX_ATTRIBUTE_ARRAY_HPP

#include <string>

#include <GL/glew.h>

#include "shader_program.hpp"
#include "vbo.hpp"

class VertAttrArr {
    private:
        GLuint attribute_location;
        const ShaderProgram *shader_program;

    public:
        VertAttrArr(const Vbo &vbo, const ShaderProgram &_shader_program,
         const std::string &attribute_name, size_t components_count,
         size_t offset);
        ~VertAttrArr();

        void enable() const;
        void disable() const;
};

#endif // VERTEX_ATTRIBUTE_ARRAY_HPP
