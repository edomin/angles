#include "img_floor.hpp"

#include <cstddef>
#include <utility>

namespace astfloor {
    #include "assets/stone_floor.h"
}
#include "exception.hpp"

namespace {
    const unsigned COLOR_COMPONENTS = 4;
    const unsigned ALPHA_CHANNEL_INDEX = 3;
    const unsigned ALPHA_SOLID = 255;
}

ImgFloor::ImgFloor()
: width(astfloor::width)
, height(astfloor::height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    uint8_t *pdata = data;
    char    *phdrdata = astfloor::header_data;
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

ImgFloor::~ImgFloor() {
    delete[] data;
}

unsigned ImgFloor::get_width() {
    return width;
}

unsigned ImgFloor::get_height() {
    return height;
}

void *ImgFloor::get_data() {
    return data;
}
