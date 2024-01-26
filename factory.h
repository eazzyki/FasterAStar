#ifndef FACTORY_H
#define FACTORY_H

#include "pathalgorithm.h"
#include "astar.h"
#include <memory>

enum AlgName {
    ASTAR,
    DIJCSTRA
};


class Factory {
public:
    static std::unique_ptr<PathAlgorithm> makeInstance(AlgName alg);
};

#endif // FACTORY_H
