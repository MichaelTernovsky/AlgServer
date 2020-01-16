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
  Searcher<T,S> *searcher;

 public:
  OA(Searcher<T,S> *s) {
    this->searcher = s;
  }

  S solve(P p) {
    MatrixProblem<T> *problem = new MatrixProblem<T>(p);
    State<string> st = new State<string>()
    problem->getAllPossibleStates()
    return this->searcher->search(problem);
  };
};

#endif //EX4__OA_H_