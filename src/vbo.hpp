#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>

class Vbo {
    private:
        GLuint id;
        size_t vertices_size;

    public:
        Vbo();
        ~Vbo();

        void bind() const;
        void unbind() const;

        void set_vertices(void *vertices, size_t count);
};

#endif // VBO_HPP
