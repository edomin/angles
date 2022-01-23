#ifndef IMG_CHARACTERS_HPP
#define IMG_CHARACTERS_HPP

#include <cstdint>

#include "iimg.hpp"

class ImgCharacters: public IImg {
    private:
        unsigned width;
        unsigned height;
        uint8_t *data;

    public:
        ImgCharacters();
        ~ImgCharacters() override;

        unsigned get_width() override;
        unsigned get_height() override;
        void *get_data() override;
};

#endif // IMG_CHARACTERS_HPP
