#include "img_characters.hpp"

#include <cstddef>
#include <utility>

namespace astchr {
    #include "assets/rpg_characters.h"
}
#include "exception.hpp"

namespace {
    const unsigned COLOR_COMPONENTS = 4;
    const unsigned ALPHA_CHANNEL_INDEX = 3;
    const unsigned ALPHA_SOLID = 255;
}

ImgCharacters::ImgCharacters()
: width(astchr::width)
, height(astchr::height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    uint8_t *pdata = data;
    char    *phdrdata = astchr::header_data;
    size_t   pixels_count = width * height;

    if (!data)
        ANG_THROW("new failed");

    for (size_t i = 0; i < pixels_count; i++) {
        pdata[ALPHA_CHANNEL_INDEX] = ALPHA_SOLID;
        HEADER_PIXEL(phdrdata, pdata);

        // I think gimp header image contains pixel channels in reverse order
        // or I dont understand something
        std::swap(pdata[0], pdata[3]);
        std::swap(pdata[1], pdata[2]);

        pdata += COLOR_COMPONENTS;
    }
}

ImgCharacters::~ImgCharacters() {
    delete[] data;
}

unsigned ImgCharacters::get_width() {
    return width;
}

unsigned ImgCharacters::get_height() {
    return height;
}

void *ImgCharacters::get_data() {
    return data;
}
