#ifndef PATHALGORITHM_H
#define PATHALGORITHM_H


#include <QGraphicsItem>

#include <iostream>
#include <unordered_map>
#include <math.h>

#include <stats.h>


class PathAlgorithm {
protected:
    std::vector<bool> grid1d;
    int widthGrid, heightGrid, cellLength;
    Cell start, goal;
    Path shortestPath;

public:

    Stats stats;

    PathAlgorithm();
    PathAlgorithm(int width, int height, int cellLength, QList<QPointF> list);

    Cell cellGlobal2cellLocal(Cell cell);
    Cell cellLocal2cellGlobal(Cell cell);
    unsigned long cell2index(Cell cell);
    unsigned long cell2index(QPointF cell);
    void index2cell(unsigned long index, Cell& cell);
    bool isValidCell(Cell cell);
    bool isTraversableCell(Cell cell);
    bool isOccupiedCell(Cell cell);

    std::vector<Cell> successors(Cell cell);
    int searchIndex(const std::vector<Cell>& container, const Cell& cell);
    bool contains(const std::vector<Cell>& container, const Cell& cell);
    Cell findMinF(std::unordered_map<unsigned long, Cell>& map);
    bool contains(const std::unordered_map<unsigned long, Cell>& map, const Cell& cell);

    void setStart(QPointF start);
    void setGoal(QPointF goal);

    void initialize(int width, int height, int cellLength, QList<QPointF> list);

    virtual Path computePath() = 0;
};

#endif // PATHALGORITHM_H
