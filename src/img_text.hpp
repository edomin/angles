#ifndef IMG_TEXT_HPP
#define IMG_TEXT_HPP

#include <cstdint>

#include "iimg.hpp"

class ImgText: public IImg {
    private:
        unsigned width;
        unsigned height;
        uint8_t *data;

    public:
        ImgText();
        ~ImgText() override;

        unsigned get_width() override;
        unsigned get_height() override;
        void *get_data() override;
};

#endif // IMG_TEXT_HPP
