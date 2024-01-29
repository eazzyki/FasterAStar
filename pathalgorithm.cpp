#include "pathalgorithm.h"

PathAlgorithm::PathAlgorithm() {

}


PathAlgorithm::PathAlgorithm(int width, int height, int cellLength, QList<QPointF> p)
{
    this->widthGrid = width/cellLength;
    this->heightGrid = height/cellLength;
    this->cellLength = cellLength;
    this->grid1d.resize(widthGrid*heightGrid, false);

    // fill 1dgrid with obstacles
    for (QPointF point : p) {
        long idx = cell2index(point);
        this->grid1d[idx] = true;
    }
}


void PathAlgorithm::initialize(int width, int height, int cellLength, QList<QPointF> list) {
    this->widthGrid = width/cellLength;
    this->heightGrid = height/cellLength;
    this->cellLength = cellLength;
    this->grid1d.resize(widthGrid*heightGrid, false);

    // fill 1dgrid with obstacles
    for (QPointF point : list) {
        long idx = cell2index(point);
        this->grid1d[idx] = true;
    }

}


Cell PathAlgorithm::cellGlobal2cellLocal(Cell cell)
{
    Cell t;
    t.x = cell.x / this->cellLength;
    t.y = cell.y / this->cellLength;
    return t;
}


Cell PathAlgorithm::cellLocal2cellGlobal(Cell cell) {
    cell.x = cell.x * this->cellLength;
    cell.y = cell.y * this->cellLength;
    return cell;
}


unsigned long PathAlgorithm::cell2index(Cell cell) {
    return this->widthGrid * cell.y + cell.x;
}


unsigned long PathAlgorithm::cell2index(QPointF cell) {
    return (this->widthGrid * cell.y() + cell.x())/this->cellLength;
}


void PathAlgorithm::index2cell(unsigned long index, Cell& cell) {
    cell.x = index % this->widthGrid;
    cell.y = index / this->widthGrid;
}


bool PathAlgorithm::isValidCell(Cell cell) {
    if(cell.x < 0 || cell.y < 0 || cell.x >= this->widthGrid || cell.y >=  this->heightGrid)  {
        return false;
    }
    return true;
}


bool PathAlgorithm::isTraversableCell(Cell cell) {
    if (!isValidCell(cell)) {
        return false;
    }

    if (this->grid1d[cell2index(cell)] == true) {
        return false;
    }
    return true;
}


std::vector<Cell> PathAlgorithm::successors(Cell cell) {
    std::vector<Cell> successors;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if (i != 0 && j != 0) {
                continue;
            }
            Cell c;
            c.x = cell.x + i;
            c.y = cell.y + j;
            if(isTraversableCell(c) && c != cell) {
                successors.push_back(c);
            }
        }
    }
    return successors;
}


int PathAlgorithm::searchIndex(const std::vector<Cell> &container, const Cell &cell) {
  int indexCell = -1;

  for (int i = 0; i < container.size(); i++) {
    if(cell == container[i]){
      indexCell = i;
      break;
    }
  }
  return indexCell;
}


typedef std::pair<unsigned long, Cell> MyPairType;
struct CompareCells {
    bool operator()(const MyPairType& left, const MyPairType& right) const {
        return left.second.f < right.second.f;
    }
};


Cell PathAlgorithm::findMinF(std::unordered_map<unsigned long, Cell> &map) {
    std::pair<unsigned long, Cell> cellWithMinF = *min_element(map.begin(), map.end(), CompareCells());
    return cellWithMinF.second;
}


Cell PathAlgorithm::findMinF(std::vector<Cell>& v) {
    int minF = int(INFINITY);
    Cell cellMinF;
    for (Cell c : v) {
        if (c.f < minF) {
            cellMinF = c;
            minF = c.f;
        }
    }
    return cellMinF;
}


bool PathAlgorithm::contains(const std::unordered_map<unsigned long, Cell> &map, const Cell &cell) {
    auto it = map.find(cell2index(cell));
    if(it != map.end()) {
        return true;
    }
    return false;
}


bool PathAlgorithm::contains(const std::vector<Cell> &container, const Cell &cell, int& idx) {
    for(int i = 0; i < container.size(); i++) {
        if(container[i] == cell) {
            idx = i;
            return true;
        }
    }
    idx = -1;
    return false;
}

bool PathAlgorithm::contains(const std::vector<Cell> &container, const Cell &cell) {
    for(int i = 0; i < container.size(); i++) {
        if(container[i] == cell) {
            return true;
        }
    }
    return false;
}


void PathAlgorithm::setStart(QPointF start) {
    this->start = Cell(start.x(), start.y());
}


void PathAlgorithm::setGoal(QPointF goal) {
    this->goal = Cell(goal.x(), goal.y());
}

