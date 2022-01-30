#include "batch_data.hpp"

BatchData::BatchData(const Texture &_texture, size_t _first_vertex_index,
 size_t _vertices_count)
: texture(&_texture)
, first_vertex_index(_first_vertex_index)
, vertices_count(_vertices_count) {}

BatchData::~BatchData() {}

[[gnu::pure]] const Texture *BatchData::get_texture() const {
    return texture;
}

[[gnu::pure]] size_t BatchData::get_first_vertex_index() const {
    return first_vertex_index;
}

[[gnu::pure]] size_t BatchData::get_vertices_count() const {
    return vertices_count;
}
