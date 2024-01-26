#include "factory.h"

std::unique_ptr<PathAlgorithm> Factory::makeInstance(AlgName alg) {
    switch (alg) {
    case ASTAR:
        return std::make_unique<AStar>();
        break;
    case DIJCSTRA:
        return nullptr;
        break;
    default:
        return nullptr;
        break;
    }
}
