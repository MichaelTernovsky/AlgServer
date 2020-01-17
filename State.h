//
// Created by michael on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_

template<typename T>
class State {
 private:
  int i;
  int j;
  T value;
  State<T> *father;
  int isVisited;

 public:
  State(int i, int j, T val) {
    this->i = i;
    this->j = j;
    this->value = val;
  }

  State(int i, int j, T val, State<T> *father) {
    this->i = i;
    this->j = j;
    this->value = val;
    this->father = father;
  }

  int getI() {
    return this->i;
  }
  int getJ() {
    return this->j;
  }
  T getValue() {
    return this->value;
  }
  State<T> *getFather() {
    return this->father;
  }
  void *setFather(State<T> *f) {
    this->father = f;
  }
  int getIsVisited() {
    return this->isVisited;
  }
  void setIsVisited(int isVisit) {
    this->isVisited = isVisit;
  }
};

#endif //EX4__STATE_H_