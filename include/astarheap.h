#ifndef ASTARHEAP_H
#define ASTARHEAP_H

#include "astar.h"

class AStarHeap : public AStar {

private:
    void goalReached(std::vector<std::vector<Cell>> parentGrid, Path& path);

public:

    void computePath(Path& path, std::vector<Cell>& visitedCells) override;

};

#endif // ASTARHEAP_H
