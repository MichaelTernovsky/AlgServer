#ifndef EX4__OA_H_
#define EX4__OA_H_

#include "Solver.h"
#include "Searcher.h"
#include "CacheManager.h"
#include "MatrixProblem.h"

template<typename P, typename S, typename T>
class OA : public Solver<P, S> {
 private:
  Searcher<T, S> *searcher;

 public:
  OA(Searcher<T, S> *s) {
    this->searcher = s;
  }

  S solve(P p) {
    MatrixProblem<T> *problem = new MatrixProblem<T>(p);
    return this->searcher->search(problem);
  }

  Solver<P, S> *createClone() {
    return new OA(this->searcher->createClone());
  }
};

#endif //EX4__OA_H_