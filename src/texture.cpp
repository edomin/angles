#include "texture.hpp"

namespace {
    const GLsizei DEFAULT_TEXTURES_COUNT = 1;
}

Texture::Texture(void *data, unsigned _width, unsigned _height)
: id()
, width(_width)
, height(_height) {
    GLenum error;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenTextures(DEFAULT_TEXTURES_COUNT, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA, width, height, 0,  GL_RGBA,
     GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

unsigned Texture::get_width() const {
    return width;
}

unsigned Texture::get_height() const {
    return height;
}
