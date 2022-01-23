#include "vao.hpp"

namespace {
    const GLsizei DEFAULT_VAO_NAMES_NUMBER = 1;
}

Vao::Vao()
: id() {
    glGenVertexArrays(DEFAULT_VAO_NAMES_NUMBER, &id);
    glBindVertexArray(id);
}

Vao::~Vao() {

}
