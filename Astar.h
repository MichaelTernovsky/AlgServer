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
#include <cmath>
#include <unordered_map>
using namespace std;
using std::priority_queue;
template<typename T, typename S>

class Astar : public Searcher<T, S> {
  int visits = 0;
  MyPriQueue<State<T> *> OPEN;
  unordered_map<State<T> *, State<T> *> CLOSED;

  S search(Searchable<T> *searchObj) {
    State<T> *n;
    State<T> *start = searchObj->getInitialState();
    State<T> *gs = searchObj->getGoalState();
    setHeuristic(searchObj);
    start->setAlgCost(start->getValue());
    OPEN.push(start);
    while (!OPEN.empty()) {
      visits++;
      n = OPEN.top(); //remove the best node from OPEN
      OPEN.pop();
      CLOSED[n] = n;
      if (searchObj->isGoalState(n)) {
        OPEN.clean();
        return (backTrace(n, searchObj));
      }
      vector<State<T> *> successors = searchObj->getAllPossibleStates(n);
      for (State<T> *s:successors) {

        double distance = n->getAlgCost() + s->getValue() + s->getHCost();
        double newCost = n->getAlgCost() + s->getValue();
        if ((CLOSED.find(s) == CLOSED.end()) && !OPEN.isExistOPEN(s)) {
          s->setAlgCost(newCost);
          s->setFather(n);
          //update the cost of s to distance. (made function set algcost.).
          OPEN.push(s);
        } else if (distance < s->getAlgCost() + s->getHCost()) {
          if (!OPEN.isExistOPEN(s)) {
            OPEN.push(s);
          } else {
            s->setAlgCost(newCost);
            //remove From Queue (c)
            removeFromQ(OPEN, s);
            //when node enters to priority queue it updates the heap
            OPEN.push(s);

          }
        }
      }
    }
    return "There is no valid path\n";
  }

  void removeFromQ(MyPriQueue<State<T> *> q, State<T> *s) {
    q.remove(s);
  }

  //return the trace to the state
  string backTrace(State<T> *n, Searchable<T> *searchObj) {
    list<State<T> *> pathLst;
    State<T> *nxt = n;
    State<T> *start = searchObj->getInitialState();
    if (nxt != nullptr) {
      pathLst.push_front(nxt);
    }
    while (!nxt->isEqual(start)) {
      nxt = nxt->getFather();
      pathLst.push_front(nxt);
    }
    return searchObj->createSolution(pathLst);
  }

  //evaluate the heuristic function with a sort of euqlidic distance.
  void setHeuristic(Searchable<T> *searchObj) {
    State<T> *state;
    State<T> *goalState = searchObj->getGoalState();
    vector<State<T> *> mapOfStates = searchObj->getStates();
    for (auto state:mapOfStates) {
      //run over all the states
      double goalX = goalState->getI();
      double goalY = goalState->getJ();
      double stateX = state->getI();
      double stateY = state->getJ();
      state->setHCost(int(round(sqrt(pow((stateX - goalX), 2) + pow((stateY - goalY), 2)))));
    }
  }

  Searcher<T, S> *createClone() {
    return new Astar();
  }
};

#endif //EX4__ASTAR_H_


