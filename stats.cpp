#include "stats.h"

Stats::Stats()
{
    this->numCellsAnalyzed = 0;
    this->pathLength = 0;
}


void Stats::increaseAnalyzedCells() {
    this->numCellsAnalyzed += 1;
}


void Stats::setPathLength(Path &path) {
    this->pathLength = path.path.size();
}


std::string Stats::getStats() {
    std::string res;
    res += "#Analyzed Cells: " + std::to_string(this->numCellsAnalyzed) + "\n";
    res += "Length of Path: " + std::to_string(this->pathLength) + "\n";
    res += "Calc time: " + std::to_string(this->calcTime.count()) + "ms" + "\n";
    return res;
}


void Stats::setCalcTime(calc_t time) {
    this->calcTime = time;
}
