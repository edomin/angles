#ifndef IIMG_HPP
#define IIMG_HPP

class IImg {
    public:
        virtual ~IImg();

        virtual unsigned get_width() = 0;
        virtual unsigned get_height() = 0;
        virtual void *get_data() = 0;
};

#endif // IIMG_HPP
