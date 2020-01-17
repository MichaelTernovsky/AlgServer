//
// Created by michael on 17/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_

#include "Searcher.h"
#include <iostream>
#include <stack>
using namespace std;

template<typename T, typename S>
class DFS : public Searcher<T, S> {
  S search(Searchable<T> *searchObj) {
    return this->runDFS(searchObj->getInitialState());
  }

  void runDFS(Searchable<T> *searchObj, State<T> *initState) {
    stack<State<T> *> stateStack;

    // push the initial state to the stack
    stateStack.push(initState);

    while (!stateStack.empty()) {
      State<T> *currState = stateStack.pop();
      // if is not visited yed
      if (currState->getIsVisited() == 0) {
        // mark as visited
        currState->setIsVisited(1);

        // get the neighbors of currState
        vector<State<T> *> vct = searchObj->getAllPossibleStates(currState);

        for (int i = 0; i < vct.size(); i++)
          stateStack.push(vct[i]);
      }
    }
  }
};

#endif //EX4__DFS_H_