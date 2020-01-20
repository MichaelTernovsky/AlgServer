//
// Created by ofir on 19/01/2020.
//

#ifndef EX4__ASTAR_H_
#define EX4__ASTAR_H_

#include "Searcher.h"
#include <iostream>
#include <queue>
#include "State.h"
#include <vector>
#include <set>
#include <iterator>
#include "BestFS.h"
#include <map>


using namespace std;
using std::priority_queue;

//Comperator to maintaine a min heap.

template<typename T, typename S>

class Astar : public Searcher<T, S> {

  MyPriQueue<State<T> *> OPEN;
  vector<State<T> *> CLOSED;

  S search(Searchable<T> *searchObj) {
    State<T> *n;
    State<T> *start = searchObj->getInitialState();
    State<T> *gs = searchObj->getGoalState();
    setHeuristic(searchObj);
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

        double distance = n->getAlgCost() + s->getValue() + s->getHCost();

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
    return "There is no valid path\n";
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

  //evaluate the heuristic function with a sort of euqlidic distance.
  void setHeuristic(Searchable<T> *searchObj) {
    State<T> *state;
    State<T> *goalState = searchObj->getGoalState();
    State<T> *states = searchObj->allStates();
    vector<State<T> *> mapOfStates = searchObj->getStates();
    for (auto state:mapOfStates) {
      //run over all the states.
      double minX = std::min(state->getI(), goalState->getI());
      double maxX = std::max(state->getI(), goalState->getI());
      double minY = std::min(state->getJ(), goalState->getJ());
      double maxY = std::max(state->getJ(), goalState->getJ());

      double absX = maxX - minX;
      double absY = maxY - minY;
      double h = std::max(absX, absY);
      state->setHCost(h);
    }
  }

    Searcher<T,S>*createClone(){
    return new Astar;
  }
  };

#endif //EX4__ASTAR_H_


