//
// Created by michael on 16/01/2020.
//

#ifndef EX4__BESTFS_H_
#define EX4__BESTFS_H_

#include "Searcher.h"
#include <iostream>
#include <queue>
#include "State.h"
#include <vector>
#include <set>
#include <iterator>

using namespace std;
using std::priority_queue;

//Comperator to maintaine a min heap.
struct Comperator {
  template<typename T>

  bool operator()(State<T> *left, State<T> *right) {
    double leftCost = left->getAlgCost();
    double rightCost = right->getAlgCost();
    return (leftCost > rightCost);
  }
};

typedef struct Comperator Comperator;

template<typename A>
class MyPriQueue : public priority_queue<A, vector<A>, Comperator> {
 public:
//check if state is at the queue
  bool isExistOPEN(A &val) const {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      if (*first == val) return true;
      ++first;
    }
    return false;
  }
};

template<typename T, typename S>
class BestFS : public Searcher<T, S> {

  MyPriQueue<State<T> *> OPEN;
  vector<State<T> *> CLOSED;

  S search(Searchable<T> *searchObj) {
    State<T> *n;
    State<T> *start = searchObj->getInitialState();
    start->setAlgCost(0);
    OPEN.push(start);
    while (!OPEN.empty()) {
      n = OPEN.top(); //remove the best node from OPEN
      OPEN.pop();
      CLOSED.push_back(n); //we want to check n again.
      if (searchObj->isGoalState(n)) {
        return (backTrace(n, searchObj));
      }
      vector<State<T> *> successors = searchObj->getAllPossibleStates(n);
      for (State<T> *s:successors) {
        double distance = n->getAlgCost() + s->getValue();
        if (!this->isExistClosed(searchObj, s) && !OPEN.isExistOPEN(s)) {
          s->setAlgCost(distance);
          s->setFather(n);
          //update the cost of s to distance. (made function set algcost.).
          OPEN.push(s);
        } else if (distance < s->getAlgCost()) {
          if (!OPEN.isExistOPEN(s)) {
            OPEN.push(s);
          } else {
            s->setAlgCost(distance);
            //remove From Queue (c)
            OPEN = removeFromQ(OPEN, s);
            //when node enters to priority queue it updates the heap
            OPEN.push(s);
          }
        }
      }
    }
    return "false";
  }

  MyPriQueue<State<T> *> removeFromQ(MyPriQueue<State<T> *> q, State<T> *s) {
    MyPriQueue<State<T> *> tmp;
    while (!q.empty()) {
      State<T> *x = q.top();
      q.pop();
      if (x != s) {
        tmp.push(x);
      }
    }
    return tmp;
  }

  //return the trace to the state
  string backTrace(State<T> *n, Searchable<T> *searchObj) {
    list<State<T> *> pathLst;
    State<T> *nxt = n;
    State<T> *start= searchObj->getInitialState();
    if (nxt != nullptr) {
      pathLst.push_front(nxt);
    }
    while (!nxt->isEqual(start)) {
      nxt = nxt->getFather();
      pathLst.push_front(nxt);
    }
    return searchObj->createSolution(pathLst);
  }

  //check if state is at the vector
  bool isExistClosed(Searchable<T> *searchObj, State<T> *state) {
    for (auto s:CLOSED) {
      if (s->isEqual(state)) {
        return true;
      }
    }
    return false;
  }
  //check if state is at the queue

};

#endif //EX4__BESTFS_H_
