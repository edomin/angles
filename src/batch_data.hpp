#ifndef BATCH_DATA_HPP
#define BATCH_DATA_HPP

#include "spritesheet.hpp"

class BatchData {
    private:
        const Texture *texture;
        ptrdiff_t      vbo_offset;
        size_t         vertices_count;

    public:
        BatchData(const Texture &_texture, ptrdiff_t _vbo_offset,
         size_t _vertices_count);
        ~BatchData();

        const Texture *get_texture() const;
        ptrdiff_t get_vbo_offset() const;
        size_t get_vertices_size() const;
        size_t get_vertices_count() const;
};

#endif // BATCH_DATA_HPP
