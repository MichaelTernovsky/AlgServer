#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include "Solver.h"
#include "Searchable.h"

template<typename T, typename S>
class Searcher {
 public:
  virtual S search(Searchable<T> *searchObj) {};
  virtual Searcher<T, S> *createClone() {};
};

#endif //EX4__SEARCHER_H_
