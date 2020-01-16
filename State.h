//
// Created by michael on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_

template<typename T>
class State {
 private:
  T *obj;
 public:
  State(T newObj) {
    this->obj = newObj;
  }
};

#endif //EX4__STATE_H_
