#include "vbo.hpp"

namespace {
    const GLsizei    DEFAULT_VBOS_COUNT = 1;
    const GLsizeiptr INITIAL_VERTICES_SIZE = sizeof(float) * 15;
    const float      DUMMY_VERTICES_DATA[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
}

Vbo::Vbo(size_t _components_per_vertex)
: id()
, components_per_vertex(_components_per_vertex)
, vertices_size(INITIAL_VERTICES_SIZE) {
    glGenBuffers(DEFAULT_VBOS_COUNT, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, DUMMY_VERTICES_DATA,
     GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vbo::~Vbo() {

}

void Vbo::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Vbo::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::set_vertices(void *vertices, size_t size) {
    if (size > vertices_size) {
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        vertices_size = size;
    } else {
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
    }
}

size_t Vbo::get_components_per_vertex() const {
    return components_per_vertex;
}
