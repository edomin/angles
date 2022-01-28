#include "img_frames.hpp"

#include <bit>
#include <cstddef>
#include <utility>

namespace astfrm {
    #include "assets/frames.hpp"
}
#include "exception.hpp"

namespace {
    constexpr unsigned COLOR_COMPONENTS = 4;
}

ImgFrames::ImgFrames()
: width(astfrm::gimp_image.width)
, height(astfrm::gimp_image.height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    size_t pixels_count = width * height;

    static_assert(astfrm::gimp_image.bytes_per_pixel == COLOR_COMPONENTS);

    for (size_t i = 0; i < pixels_count; i++) {
        size_t rindex = i * COLOR_COMPONENTS;
        size_t gindex = i * COLOR_COMPONENTS + 1;
        size_t bindex = i * COLOR_COMPONENTS + 2;
        size_t aindex = i * COLOR_COMPONENTS + 3;

        data[rindex] = astfrm::gimp_image.pixel_data[rindex];
        data[gindex] = astfrm::gimp_image.pixel_data[gindex];
        data[bindex] = astfrm::gimp_image.pixel_data[bindex];
        data[aindex] = astfrm::gimp_image.pixel_data[aindex];

        if constexpr (std::endian::native == std::endian::little) {
            std::swap(data[rindex], data[aindex]);
            std::swap(data[gindex], data[bindex]);
        }
    }
}

ImgFrames::~ImgFrames() {
    delete[] data;
}

unsigned ImgFrames::get_width() {
    return width;
}

unsigned ImgFrames::get_height() {
    return height;
}

void *ImgFrames::get_data() {
    return data;
}
