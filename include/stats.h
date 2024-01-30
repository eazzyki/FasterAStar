#ifndef STATS_H
#define STATS_H

#include <string>
#include <chrono>
#include "owntypes.h"

using calc_t = std::chrono::milliseconds;
class Stats {

private:
    long numCellsAnalyzed;
    int pathLength;
    calc_t calcTime;
    std::vector<Cell> visitedCells;

public:    
    Stats();
    void increaseAnalyzedCells();
    void setPathLength(Path& path);
    std::string getStats();
    void setCalcTime(calc_t time);
    void addVisitedCell(Cell cell);
};

#endif // STATS_H
