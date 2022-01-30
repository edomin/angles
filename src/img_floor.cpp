#include "img_floor.hpp"

#include <bit>
#include <cstddef>
#include <utility>

namespace astfloor {
    #include "assets/stone_floor.hpp"
}
#include "exception.hpp"

namespace {
    constexpr unsigned COLOR_COMPONENTS = 4;
    constexpr unsigned RED_CHANNEL_INDEX = 0;
    constexpr unsigned GREEN_CHANNEL_INDEX = 1;
    constexpr unsigned BLUE_CHANNEL_INDEX = 2;
    constexpr unsigned ALPHA_CHANNEL_INDEX = 3;
}

ImgFloor::ImgFloor()
: width(astfloor::gimp_image.width)
, height(astfloor::gimp_image.height)
, data(new uint8_t[width * height * COLOR_COMPONENTS]) {
    size_t pixels_count = width * height;

    static_assert(astfloor::gimp_image.bytes_per_pixel == COLOR_COMPONENTS);

    for (size_t i = 0; i < pixels_count; i++) {
        size_t rindex = i * COLOR_COMPONENTS + RED_CHANNEL_INDEX;
        size_t gindex = i * COLOR_COMPONENTS + GREEN_CHANNEL_INDEX;
        size_t bindex = i * COLOR_COMPONENTS + BLUE_CHANNEL_INDEX;
        size_t aindex = i * COLOR_COMPONENTS + ALPHA_CHANNEL_INDEX;

        data[rindex] = astfloor::gimp_image.pixel_data[rindex];
        data[gindex] = astfloor::gimp_image.pixel_data[gindex];
        data[bindex] = astfloor::gimp_image.pixel_data[bindex];
        data[aindex] = astfloor::gimp_image.pixel_data[aindex];

        if constexpr (std::endian::native == std::endian::little) {
            std::swap(data[rindex], data[aindex]);
            std::swap(data[gindex], data[bindex]);
        }
    }
}

ImgFloor::~ImgFloor() {
    delete[] data;
}

[[gnu::pure]] unsigned ImgFloor::get_width() {
    return width;
}

[[gnu::pure]] unsigned ImgFloor::get_height() {
    return height;
}

[[gnu::pure]] void *ImgFloor::get_data() {
    return data;
}
