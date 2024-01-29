#ifndef ASTARFAST_H
#define ASTARFAST_H

#include "astar.h"


class AStarFast : public AStar {
private:
    void goalReached(std::vector<std::vector<Cell>> parentGrid, Path& path);
public:
    void computePath(Path& path, std::vector<Cell>& visitedCells) override;
};

#endif // ASTARFAST_H
