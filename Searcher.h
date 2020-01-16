//
// Created by ofir on 16/01/2020.
//

#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include "Solver.h"
#include "Searchable.h"

template<typename T>
class Searcher {
 public:
  template<typename S>
  S search(Searchable<T> *searchObj);
};

#endif //EX4__SEARCHER_H_
