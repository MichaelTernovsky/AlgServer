//
// Created by michael on 16/01/2020.
//

#ifndef EX4__MATRIXPROBLEM_H_
#define EX4__MATRIXPROBLEM_H_

#include "Searchable.h"
#include <iostream>
using namespace std;
template<typename T>
class MatrixProblem : public Searchable<T> {

 private:
  string str;

 public:
  MatrixProblem(string str) {
    this->str = str;
  }

  State<T> getInitialState() {
    cout << "initialState@#R%@#%@" << endl;
  };
  bool isGoalState(State<T> *st) {
    cout << "goalState@#R%@#%@" << endl;

  };
  State<T> *getAllPossibleStates(State<T> *st) {
    cout << "getAllPossibleStates@#R%@#%@" << endl;

  };
};

#endif //EX4__MATRIXPROBLEM_H_