#include "factory.h"

std::unique_ptr<PathAlgorithm> Factory::makeInstance(AlgName alg) {
    switch (alg) {
    case ASTARFAST:
        return std::make_unique<AStarFast>();
        break;
    case ASTARHEAP:
        return std::make_unique<AStarHeap>();
        break;
    case DIJKSTRA:
        return std::make_unique<Dijkstra>();
        break;
    }
}

