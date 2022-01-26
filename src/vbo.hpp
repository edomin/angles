#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>

class Vbo {
    private:
        GLuint id;
        size_t components_per_vertex;
        size_t vertices_size;

    public:
        Vbo(size_t _components_per_vertex);
        ~Vbo();

        void bind() const;
        void unbind() const;

        void set_vertices(void *vertices, size_t count);

        size_t get_components_per_vertex() const;
};

#endif // VBO_HPP
