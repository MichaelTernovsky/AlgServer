//
// Created by ofir on 16/01/2020.
//

#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include "Solver.h"
#include "Searchable.h"
template<typename P, typename S>
class Searcher:Solver<P,S> {
 public:
  template<typename T>
  S search(Searchable<T> srchObj);

};

#endif //EX4__SEARCHER_H_
