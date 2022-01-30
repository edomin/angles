#include "game/search.hpp"

namespace game {

Search::Search(unsigned _width, unsigned _height)
: width(_width)
, height(_height)
, data() {}

Search::~Search() {}

Search& Search::operator=(const Search &other) {
    if (&other != this) {
        width = other.width;
        height = other.height;
        data = other.data;
    }

    return *this;
}

[[gnu::pure]] bool Search::operator==(const Search &other) const {
    bool width_equals = width == other.width;
    bool height_equals = height == other.height;
    bool data_equals = data == other.data;

    return width_equals && height_equals && data_equals;
}

void Search::clear() {
    data.clear();
    data.insert(data.begin(), width * height, 0);
}

void Search::set(const Cell &cell, unsigned value) {
    data[cell.row * width + cell.col] = value;
}

[[gnu::pure]] unsigned Search::at(const Cell &cell) const {
    return data[cell.row * width + cell.col];
}

[[gnu::pure]] unsigned Search::at(unsigned row, unsigned col) const {
    return data[row * width + col];
}

} // game::
