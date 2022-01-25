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

// namespace debug {

// inline void check_opengl_error() {
//     GLenum error = glGetError();

//     if (error != GL_NO_ERROR)
//         ANG_THROW(reinterpret_cast<const char *>(gluErrorString(error)));
// }

// } // debug::

#endif // DEBUG_HPP
