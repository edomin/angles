#ifndef IMG_FLOOR_HPP
#define IMG_FLOOR_HPP

#include <cstdint>

#include "iimg.hpp"

class ImgFloor: public IImg {
    private:
        unsigned width;
        unsigned height;
        uint8_t *data;

    public:
        ImgFloor();
        ~ImgFloor() override;

        unsigned get_width() override;
        unsigned get_height() override;
        void *get_data() override;
};

#endif // IMG_FLOOR_HPP
