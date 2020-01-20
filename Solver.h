//
// Created by michael on 09/01/2020.
//

#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_

// Interface

// P - problem S - solution
template<typename P, typename S>
class Solver {
 public:
  // the method gets problem P and returns solution S
  virtual S solve(P p) {};
  virtual Solver<P, S> *createClone() {};
};

#endif //EX4__SOLVER_H_