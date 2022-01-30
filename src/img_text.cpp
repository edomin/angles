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
    constexpr unsigned RED_CHANNEL_INDEX = 0;
    constexpr unsigned GREEN_CHANNEL_INDEX = 1;
    constexpr unsigned BLUE_CHANNEL_INDEX = 2;
    constexpr unsigned ALPHA_CHANNEL_INDEX = 3;
}

ImgText::ImgText()
: width(asttxt::gimp_image.width)
, height(asttxt::gimp_image.height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    size_t pixels_count = width * height;

    static_assert(asttxt::gimp_image.bytes_per_pixel == COLOR_COMPONENTS);

    for (size_t i = 0; i < pixels_count; i++) {
        size_t rindex = i * COLOR_COMPONENTS + RED_CHANNEL_INDEX;
        size_t gindex = i * COLOR_COMPONENTS + GREEN_CHANNEL_INDEX;
        size_t bindex = i * COLOR_COMPONENTS + BLUE_CHANNEL_INDEX;
        size_t aindex = i * COLOR_COMPONENTS + ALPHA_CHANNEL_INDEX;

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
