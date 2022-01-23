#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

#define ANG_THROW(INFO) \
 throw Exception(__FILE__, __LINE__, __PRETTY_FUNCTION__, INFO)

class Exception: public std::exception {
    public:
        std::string errortext;

    public:
        Exception(const Exception&) = delete;
        Exception& operator=(const Exception&) = delete;

        Exception(const char *_file, int _line, const char *_func,
         const char *_info = "");

        const char *what() const noexcept override final;
};

#endif // EXCEPTION_HPP
