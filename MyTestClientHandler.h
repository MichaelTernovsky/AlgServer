//
// Created by michael on 09/01/2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler {
 private:
  Solver<P, S> s; // P - problem S - solution
  CacheManager<Solver<P, S>> ch;
 public:
  /**
   * CTOR
   * @param s - the solver
   * @param ch - the cache manager
   */
  MyTestClientHandler(Solver<P, S> s, CacheManager<Solver<P, S>> ch) {
    this->s = s;
    this->ch = ch;
  }

  /**
   * getSolver - if the solution (solver) is in the cache
   * manager we return it. Otherwise we create and return it.
   * @param line - the string line we get from the user.
   * @return Solver<P, S> - the solver object.
   */
  S getSolver(string line) {
    if (this->ch.isExist(s) == 1) {
      return this->ch.get(line);
    } else {
      return this->s.solve(line);
    }
  }
};

#endif //EX4__MYTESTCLIENTHANDLER_H_