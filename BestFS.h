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

template<typename T>
class MyPriQueue : public std::priority_queue<T, std::vector<T>>
{
 public:

  //remove state from queue and update the priority heap
  bool remove(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
      this->c.erase(it);
      std::make_heap(this->c.begin(), this->c.end(), this->comp);
      return true;
    }
    else {
      return false;
    }
  }

  //check if state is at the queue
  bool isExistOPEN(const T&val) const
  {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first!=last) {
      if (*first==val) return true;
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
        double distance = n->getAlgCost() + s->getAlgCost();
        if (!this->isExistClosed(searchObj, s) && !OPEN.isExistOPEN(s)) {
          s->setFather(n);
          //update the cost of s to distance. (made function set algcost.).
          OPEN.push(s);
        } else if (distance < s->getAlgCost()) {
          if (!OPEN.isExistOPEN(s)) {
            OPEN.push(s);
          } else {
            s->setAlgCost(distance);
            //remove From Queue (c)
            OPEN.remove(s);
            //when node enters to priority queue it updates the heap
            OPEN.push(s);
          }
        }
      }
    }
    return "false";
  }

  //return the trace to the state
  string backTrace(State<T> *n, Searchable<T> *searchObj) {
    list<State<T> *> pathLst;
    State<T> * nxt = n;
    if (nxt != nullptr) {
      pathLst.push_front(nxt);
    }
    while (nxt != searchObj->getInitialState()) {
      nxt = nxt->getFather();
      pathLst.push_front(nxt);
    }
    return searchObj->createSolution(pathLst);
  }

  //check if state is at the vector
  bool isExistClosed(Searchable<T> *searchObj, State<T> *state) {
    for (auto s:CLOSED) {
      if (searchObj->isEqual(s, state)) {
        return true;
      }
    }
    return false;
  }
  //check if state is at the queue
//  bool isExistOPEN(Searchable<T> *searchObj, State<T> *state) {
//    for (auto s:OPEN) {
//      if (searchObj->isEqual(s, state)) {
//        return true;
//      }
//    }
//    return false;
//  }
};

#endif //EX4__BESTFS_H_
