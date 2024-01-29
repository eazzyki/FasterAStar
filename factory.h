#ifndef FACTORY_H
#define FACTORY_H

#include "pathalgorithm.h"
#include "astarfast.h"
#include "astarheap.h"
#include "dijkstra.h"
#include <memory>

enum AlgName {
    ASTARFAST,
    ASTARHEAP,
    DIJKSTRA
};


class Factory {
public:
    static std::unique_ptr<PathAlgorithm> makeInstance(AlgName alg);
};

#endif // FACTORY_H
