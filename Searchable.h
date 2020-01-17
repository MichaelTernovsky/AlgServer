//
// Created by ofir on 16/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include "State.h"
#include <vector>
using namespace std;

template<typename T>
class Searchable {
 public:
  virtual State<T> *getInitialState() {};
  virtual bool isGoalState(State<T> *st) {};
  virtual vector<State<T> *> getAllPossibleStates(State<T> *s) {};
};

#endif //EX4__SEARCHABLE_H_
