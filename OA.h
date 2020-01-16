//
// Created by ofir on 16/01/2020.
//

#ifndef EX4__OA_H_
#define EX4__OA_H_

#include "Solver.h"
#include "Searcher.h"
#include "CacheManager.h"
#include "MatrixProblem.h"

template<typename P, typename S, typename T>
class OA : public Solver<P, S> {
 private:
  Searcher<T> *searcher;

 public:
  OA(Searcher<T> *s) {
    this->searcher = s;
  }

  S solve(P p) {
    return this->searcher->search(p);
  };
};

#endif //EX4__OA_H_