#ifndef GAME_CELL_HPP
#define GAME_CELL_HPP

namespace game {

class Cell {
    public:
        unsigned row;
        unsigned col;

        Cell(unsigned _row, unsigned _col);
        Cell(const Cell &other);
        ~Cell();

        Cell& operator=(const Cell &other);
        bool operator==(const Cell &other) const;
};

} // game::

#endif // GAME_CELL_HPP
