#include "img_text.hpp"

#include <bit>
#include <cstddef>
#include <utility>

namespace asttxt {
    #include "assets/text.hpp"
}
#include "exception.hpp"

namespace {
    constexpr unsigned COLOR_COMPONENTS = 4;
}

ImgText::ImgText()
: width(asttxt::gimp_image.width)
, height(asttxt::gimp_image.height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    size_t pixels_count = width * height;

    static_assert(asttxt::gimp_image.bytes_per_pixel == COLOR_COMPONENTS);

    for (size_t i = 0; i < pixels_count; i++) {
        size_t rindex = i * COLOR_COMPONENTS;
        size_t gindex = i * COLOR_COMPONENTS + 1;
        size_t bindex = i * COLOR_COMPONENTS + 2;
        size_t aindex = i * COLOR_COMPONENTS + 3;

        data[rindex] = asttxt::gimp_image.pixel_data[rindex];
        data[gindex] = asttxt::gimp_image.pixel_data[gindex];
        data[bindex] = asttxt::gimp_image.pixel_data[bindex];
        data[aindex] = asttxt::gimp_image.pixel_data[aindex];

        if constexpr (std::endian::native == std::endian::little) {
            std::swap(data[rindex], data[aindex]);
            std::swap(data[gindex], data[bindex]);
        }
    }
}

ImgText::~ImgText() {
    delete[] data;
}

unsigned ImgText::get_width() {
    return width;
}

unsigned ImgText::get_height() {
    return height;
}

void *ImgText::get_data() {
    return data;
}
