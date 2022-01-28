#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <GL/glew.h>

#include "exception.hpp"

#define CHECK_OPENGL_ERROR() \
{ \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) \
        ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error))); \
}

inline void _print_lineno(const char *function, const char *file, int line) {
    std::cout << function << "(), " << file << ":" << line << std::endl;
}

#define print_lineno() _print_lineno(__func__, __FILE__, __LINE__)

#endif // DEBUG_HPP
