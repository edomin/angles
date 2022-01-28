#ifndef IMG_FRAMES_HPP
#define IMG_FRAMES_HPP

#include <cstdint>

#include "iimg.hpp"

class ImgFrames: public IImg {
    private:
        unsigned width;
        unsigned height;
        uint8_t *data;

    public:
        ImgFrames();
        ~ImgFrames() override;

        unsigned get_width() override;
        unsigned get_height() override;
        void *get_data() override;
};

#endif // IMG_FRAMES_HPP
