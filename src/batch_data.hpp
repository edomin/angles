#ifndef BATCH_DATA_HPP
#define BATCH_DATA_HPP

#include "spritesheet.hpp"

class BatchData {
    private:
        const Texture *texture;
        size_t         first_vertex_index;
        size_t         vertices_count;

    public:
        BatchData(const Texture &_texture, size_t _first_vertex_index,
         size_t _vertices_count);
        ~BatchData();

        const Texture *get_texture() const;
        size_t get_first_vertex_index() const;
        size_t get_vertices_count() const;
};

#endif // BATCH_DATA_HPP
