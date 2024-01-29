#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "astar.h"

class Dijkstra : public AStar {
private:
    void goalReached(std::vector<std::vector<Cell>> parentGrid, Path& path);
public:
    void computePath(Path& path, std::vector<Cell>& visitedCells) override;
};

#endif // DIJKSTRA_H
