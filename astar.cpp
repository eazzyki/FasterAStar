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


Path AStar::computePath() {

    Cell start = cellGlobal2cellLocal(this->start);
    Cell goal = cellGlobal2cellLocal(this->goal);
    Path path;

    std::unordered_map<unsigned long, Cell> open_list;
    std::unordered_map<unsigned long, Cell> closed_list;
    std::vector<std::vector<Cell>> parent_array;
    parent_array.resize(this->widthGrid, std::vector<Cell>(this->heightGrid));

    open_list.insert({cell2index(start), start});
    //std::make_heap(open_list.begin(), open_list.end(), std::greater<>{});

    while (!open_list.empty()) {
        // get cell with lowest f from open_list
        Cell currentCell = findMinF(open_list);
        this->stats.increaseAnalyzedCells();

//        std::cout << currentCell << std::endl;
        // remove currentCell from open_list
        open_list.erase(cell2index(currentCell));

        if (currentCell == goal) {
            goalReached(parent_array, path);
            break;
        }

        for(Cell successorCell : successors(currentCell)) {

            // check if successor is in closed_list
            if(contains(closed_list, successorCell)) {
                continue;
            }

            // compute g, h and f
            successorCell.g = computeG(currentCell, successorCell);
            successorCell.h = computeH(successorCell, goal);
            successorCell.f = successorCell.g + successorCell.h;


            // check if successor is already in open_list with smaller f -> skip successor
            auto successor_it = open_list.find(cell2index(successorCell));

            if (successor_it != open_list.end()) {
                if (successorCell < successor_it->second) {
                    successor_it->second = successorCell;
                    parent_array[successorCell.x][successorCell.y] = currentCell;
                }
            } else {
                open_list.insert({cell2index(successorCell), successorCell});
                parent_array[successorCell.x][successorCell.y] = currentCell;
            }
        }
        closed_list.insert({cell2index(currentCell), currentCell});
    }

    return path;
}


void AStar::goalReached(std::vector<std::vector<Cell> > parentGrid, Path &path) {
    Cell currentCell = cellGlobal2cellLocal(this->goal);
    Cell startLocal = cellGlobal2cellLocal(this->start);
    while (currentCell != startLocal) {
        currentCell = parentGrid[currentCell.x][currentCell.y];
        path.push_back(currentCell);
    }
    path.path.pop_back();

    this->stats.setPathLength(path);
}
