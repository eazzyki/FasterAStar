#ifndef ASTAR_H
#define ASTAR_H

#include "pathalgorithm.h"

class AStar : public PathAlgorithm {

public:

    Path computePath() override;

private:

    double computeG(Cell start, Cell dest);
    double computeH(Cell start, Cell dest);

    void goalReached(std::vector<std::vector<Cell>> parentGrid, Path& path);
};

#endif // ASTAR_H
