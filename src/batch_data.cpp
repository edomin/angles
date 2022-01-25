#include "batch_data.hpp"

BatchData::BatchData(const Texture &_texture, ptrdiff_t _vbo_offset,
 size_t _vertices_count)
: texture(&_texture)
, vbo_offset(_vbo_offset)
, vertices_count(_vertices_count) {}

BatchData::~BatchData() {}

const Texture *BatchData::get_texture() const {
    return texture;
}

ptrdiff_t BatchData::get_vbo_offset() const {
    return vbo_offset;
}

size_t BatchData::get_vertices_size() const {
    return vertices_count * 5 * sizeof(float);
}

size_t BatchData::get_vertices_count() const {
    return vertices_count;
}
