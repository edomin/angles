#ifndef GAME_SEARCH_HPP
#define GAME_SEARCH_HPP

#include <vector>

#include "game/cell.hpp"

namespace game {

class Search {
    public:
        unsigned              width;
        unsigned              height;
        std::vector<unsigned> data;

        Search(unsigned _width, unsigned _height);
        ~Search();

        Search& operator=(const Search &other);
        bool operator==(const Search &other) const;

        void clear();
        void set(const Cell &cell, unsigned value);
        unsigned at(const Cell &cell) const;
        unsigned at(unsigned row, unsigned col) const;
};

} // game::

#endif // GAME_SEARCHING_CELL_RECORD_HPP
