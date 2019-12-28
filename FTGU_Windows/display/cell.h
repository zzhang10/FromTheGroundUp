#ifndef CELL_H
#define CELL_H
#include "../subject.h"

struct Cell final : public Subject{
    int chamberNumber;
    Cell(int y, int x, int chamberNumber, bool canWalk, char defaultChar);
};

#endif


