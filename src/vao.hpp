#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>

class Vao {
    private:
        GLuint id;

    public:
        Vao();
        ~Vao();

        void bind();
};

#endif // VAO_HPP
