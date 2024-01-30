#include "astar.h"
#include <QDebug>

/**
 * Decide which heuristic to use.
 * 0: Euclidean
 * 1: Manhattan
 */
# define HEURISTIC 0


double AStar::computeG(Cell start, Cell dest) {
    double distBetweenCells = sqrt(pow(start.x - dest.x, 2) + pow(start.y - dest.y, 2));
    return start.g + distBetweenCells;
}


double AStar::computeH(Cell start, Cell dest) {
    switch (HEURISTIC) {
        case 0:
            return sqrt(pow(start.x - dest.x, 2) + pow(start.y - dest.y, 2));
            break;
        case 1:
            return abs(start.x - dest.x) + abs(start.y - dest.y);
            break;
    }
    return -1;
}
