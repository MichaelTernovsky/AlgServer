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
  double Hcost;

 public:
  State(int i, int j, T val) {
    this->i = i;
    this->j = j;
    this->value = val;
    this->father = nullptr;
    algCost = 0;
    Hcost = 0;
  }

  State(int i, int j, T val, State<T> *father) {
    this->i = i;
    this->j = j;
    this->value = val;
    this->father = father;
    this->father = nullptr;
    algCost = 0;
    Hcost = 0;
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
  double getAlgCost() {
    return this->algCost;
  }
  double setAlgCost(double c) {
    this->algCost = c;
  }

  double getHCost() {
    return this->Hcost;
  }
  double setHCost(double hc) {
    this->Hcost = hc;
  }

};

#endif //EX4__STATE_H_