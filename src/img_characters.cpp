#include "img_characters.hpp"

#include <bit>
#include <cstddef>
#include <utility>

namespace astchr {
    #include "assets/rpg_characters.hpp"
}
#include "exception.hpp"

namespace {
    constexpr unsigned COLOR_COMPONENTS = 4;
    constexpr unsigned RED_CHANNEL_INDEX = 0;
    constexpr unsigned GREEN_CHANNEL_INDEX = 1;
    constexpr unsigned BLUE_CHANNEL_INDEX = 2;
    constexpr unsigned ALPHA_CHANNEL_INDEX = 3;
}

ImgCharacters::ImgCharacters()
: width(astchr::gimp_image.width)
, height(astchr::gimp_image.height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    size_t pixels_count = width * height;

    static_assert(astchr::gimp_image.bytes_per_pixel == COLOR_COMPONENTS);

    for (size_t i = 0; i < pixels_count; i++) {
        size_t rindex = i * COLOR_COMPONENTS + RED_CHANNEL_INDEX;
        size_t gindex = i * COLOR_COMPONENTS + GREEN_CHANNEL_INDEX;
        size_t bindex = i * COLOR_COMPONENTS + BLUE_CHANNEL_INDEX;
        size_t aindex = i * COLOR_COMPONENTS + ALPHA_CHANNEL_INDEX;

        data[rindex] = astchr::gimp_image.pixel_data[rindex];
        data[gindex] = astchr::gimp_image.pixel_data[gindex];
        data[bindex] = astchr::gimp_image.pixel_data[bindex];
        data[aindex] = astchr::gimp_image.pixel_data[aindex];

        if constexpr (std::endian::native == std::endian::little) {
            std::swap(data[rindex], data[aindex]);
            std::swap(data[gindex], data[bindex]);
        }
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
