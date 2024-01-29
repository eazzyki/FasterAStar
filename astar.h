#ifndef ASTAR_H
#define ASTAR_H

#include "pathalgorithm.h"

class AStar : public PathAlgorithm {

public:

    virtual void computePath(Path& path, std::vector<Cell>& visitedCells) = 0;

protected:

    double computeG(Cell start, Cell dest);
    double computeH(Cell start, Cell dest);

};

#endif // ASTAR_H
