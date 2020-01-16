//
// Created by ofir on 16/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
template<typename T>
class State{
  ///
  /////open State Object!
  ///
  ///
  ///
};

template<typename T>
class Searchable {
 public:
virtual State<T> getInitialState();
virtual bool isGoalState(State<T> st);
virtual State<T>[4] getAllPossibleStates(State<T>);
};

#endif //EX4__SEARCHABLE_H_
