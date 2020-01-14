//
// Created by michael on 09/01/2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_

#include "CacheManager.h"
#include "Solver.h"

template<typename P, typename S>
class FileCacheManager : CacheManager<P, S> {
  Solver<P, S> findSolution(string str);
};


#endif //EX4__FILECACHEMANAGER_H_