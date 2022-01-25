#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <GL/glew.h>

class Texture {
    private:
        GLuint   id;
        unsigned width;
        unsigned height;

    public:
        Texture(void *data, unsigned _width, unsigned _height);
        ~Texture();

        void bind() const;

        unsigned get_width() const;
        unsigned get_height() const;

};

#endif // TEXTURE_HPP

