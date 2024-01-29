#include "astarheap.h"

void AStarHeap::goalReached(std::vector<std::vector<Cell> > parentGrid, Path &path) {
    Cell currentCell = cellGlobal2cellLocal(this->goal);
    Cell startLocal = cellGlobal2cellLocal(this->start);
    while (currentCell != startLocal) {
        currentCell = parentGrid[currentCell.x][currentCell.y];
        path.push_back(currentCell);
    }
    path.path.pop_back();

    this->stats.setPathLength(path);
}


void AStarHeap::computePath(Path &path, std::vector<Cell> &visitedCells) {
    Cell start = cellGlobal2cellLocal(this->start);
    Cell goal = cellGlobal2cellLocal(this->goal);

    std::vector<Cell> open_list;
    std::vector<Cell> closed_list;
    std::vector<std::vector<Cell>> parent_array;
    parent_array.resize(this->widthGrid, std::vector<Cell>(this->heightGrid));

    open_list.push_back(start);
//    std::make_heap(open_list.begin(), open_list.end(), std::greater<>{});

    int idxSuccessor;
    while (!open_list.empty()) {
        // get cell with lowest f from open_list
        std::make_heap(open_list.begin(), open_list.end(), std::greater<>());
        std::pop_heap(open_list.begin(), open_list.end(), std::greater<>());
        Cell currentCell = open_list.back();

        this->stats.increaseAnalyzedCells();

//        std::cout << currentCell << std::endl;
        // remove currentCell from open_list
        open_list.pop_back();

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
            if (contains(open_list, successorCell, idxSuccessor)) {
                if (successorCell < open_list[idxSuccessor]) {
                    open_list[idxSuccessor] = successorCell;
                    parent_array[successorCell.x][successorCell.y] = currentCell;
                }
            } else {
                open_list.push_back(successorCell);
                parent_array[successorCell.x][successorCell.y] = currentCell;
            }
        }
        closed_list.push_back(currentCell);
        if(currentCell != start) {
            visitedCells.push_back(currentCell);
        }
    }
}


