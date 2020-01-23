#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include "Searcher.h"
#include <iostream>
#include <queue>
#include <list>
using namespace std;

template<typename T, typename S>
class BFS : public Searcher<T, S> {
  S search(Searchable<T> *searchObj) {
    int visits = 0;
    if (searchObj->getInitialState()->getValue() == -1) {
      std::cerr << "Initial point is -1" << std::endl;
      S str = "Initial point is -1\n";
      return str;
    } else {

      queue<State<T> *> stateQueue;
      list<State<T> *> lst;

      // push the initial state to the stack
      State<T> *initState = searchObj->getInitialState();
      stateQueue.push(initState);

      State<T> *currState = NULL;
      while (!stateQueue.empty()) {
        visits++;
        currState = stateQueue.front();
        stateQueue.pop();

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
            if (!isInList(lst, neighbor)) {
              neighbor->setFather(currState); // update the father
            }
            stateQueue.push(vct[i]);
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

      string str = searchObj->createSolution(pathLst);
      cout << visits << endl;
      return str;
    }
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

  Searcher<T, S> *createClone() {
    return new BFS();
  }
};

#endif //EX4__BFS_H_