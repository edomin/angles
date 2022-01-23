#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <GL/glew.h>

class Texture {
    private:
        GLuint id;

    public:
        Texture(void *data, unsigned width, unsigned height);
        ~Texture();

};

#endif // TEXTURE_HPP

