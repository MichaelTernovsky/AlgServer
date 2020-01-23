#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include "State.h"
#include <vector>
#include <string>
#include <list>
using namespace std;

template<typename T>
class Searchable {
 public:
  virtual State<T> *getInitialState() {};
  virtual bool isGoalState(State<T> *st) {};
  virtual State<T> *getGoalState() {};
  virtual vector<State<T> *> getAllPossibleStates(State<T> *s) {};
  virtual bool isEqual(State<T> *st1, State<T> *st2) {};
  virtual string createSolution(list<State<T> *> pathLst) {};
  virtual vector<State<T> *> getStates() {};

};

#endif //EX4__SEARCHABLE_H_
