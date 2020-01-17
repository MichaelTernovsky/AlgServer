//
// Created by michael on 17/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_

#include "Searcher.h"
#include <iostream>
#include <stack>
#include <list>
using namespace std;

template<typename T, typename S>
class DFS : public Searcher<T, S> {
  S search(Searchable<T> *searchObj) {
    stack<State<T> *> stateStack;
    list<State<T> *> lst;

    // push the initial state to the stack
    State<T> *initState = searchObj->getInitialState();
    stateStack.push(initState);

    State<T> *currState = NULL;
    while (!stateStack.empty()) {
      currState = stateStack.top();
      stateStack.pop();

      if (searchObj->isGoalState(currState)) {
        break;
      }
      // if is not visited yet - not is the list
      if (!isInList(lst, currState)) {
        // mark as visited - insert to the list
        lst.push_front(currState);

        // get the neighbors of currState
        vector<State<T> *> vct = searchObj->getAllPossibleStates(currState);

        for (int i = 0; i < vct.size(); i++) {
          State<T> *neighbor = vct[i];
          neighbor->setFather(currState); // update the father
          stateStack.push(vct[i]);
        }
      }
    }

    list<State<T> *> pathLst;
    // finding the way from start state to end state
    while (currState != NULL && currState->getFather() != NULL) {
      pathLst.push_front(currState);
      currState = currState->getFather();
    }

    if (!pathLst.empty())
      pathLst.push_front(initState);

    string str = "";
    for (auto x:pathLst) {
      State<T> *obj = x;
      str += obj->getValue();
      str += "->";
    }

//    // creating the path string
//    S str = "";
//    for (auto x:pathLst) {
//      State<T> *state = pathLst.front();
//      pathLst.pop_front();
//
//      int currI = state->getI();
//      int currJ = state->getJ();
//      if (state->getFather() != NULL) {
//        int fatherI = state->getFather()->getI();
//        int fatherJ = state->getFather()->getJ();
//
//        if (currI == fatherI + 1) {
//          str += "UP -> ";
//        }
//
//        if (currJ == fatherJ + 1) {
//          str += "UP -> ";
//        }
//        if (currI == fatherI + 1) {
//          str += "UP -> ";
//        }
//        if (currI == fatherI + 1) {
//          str += "UP -> ";
//        }
//
//      } else
//        break;
//    }

    return str;
  }

  bool isInList(list<State<T> *> lst, State<T> *s) {
    if (lst.empty())
      return false;

    for (auto x:lst) {
      State<T> *tmp = x;
      if (tmp->isEqual(s))
        return true;
    }
    return false;
  }
};

#endif //EX4__DFS_H_