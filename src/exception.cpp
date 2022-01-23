#include "exception.hpp"

#include <iostream>
#include <sstream>

Exception::Exception(const char *_file, int _line, const char *_func,
 const char *_info)
: errortext() {
    std::stringstream sstream;

    sstream << _file << ":" << _line << ": " << _func;
    if (_info)
        sstream << ": " << _info;

    errortext.append(sstream.str());
}

const char *Exception::what() const noexcept {
    return errortext.c_str();
}
