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
  double algCost;

 public:
  State(int i, int j, T val) {
    this->i = i;
    this->j = j;
    this->value = val;
    this->father = nullptr;
  }

  State(int i, int j, T val, State<T> *father) {
    this->i = i;
    this->j = j;
    this->value = val;
    this->father = father;
    this->father = nullptr;
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
  bool isEqual(State<T> *st1) {
    return ((st1->getI() == this->getI()) && (st1->getJ() == this->getJ())
        && (st1->getValue() == this->getValue()));
  }
  double getAlgCost(){
    return this->algCost;
  }
  double setAlgCost(int c){
    this->algCost = c;
  }
};

#endif //EX4__STATE_H_