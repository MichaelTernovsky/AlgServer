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

template<typename T,typename S>
class BestFS : public Searcher<T, S> {

  priority_queue <State<T>*> OPEN;
  vector<State<T> *>  CLOSED;
  vector<State<T> *> path;

  S search(Searchable<T> *searchObj) {
    State<T> *n;
    State<T> *start = searchObj->getInitialState();
    start->setAlgCost(0);
    OPEN.push(start);
    while (!OPEN.empty()){
      n = OPEN.top(); //remove the best node from OPEN
      OPEN.pop();
      CLOSED.push(n); //we want to check n again.
      if(searchObj->isGoalState(n)){
        path = backTrace(n,searchObj);
        return path;
      }
      vector<State<T> *> successors = searchObj->getAllPossibleStates(n);
      for(State<T>  *s:successors){
        double distance = n->getAlgCost()+ s->getAlgCost();
        if(!this->isExistClosed(s)&&!this->isExistOPEN(s)){
          s->setFather(n);
          //update the cost of s to distance. (made function set algcost.).
          OPEN.push(s);
        }
        else if(distance < s->getAlgCost()){
          if(!this->isExistOPEN(s)){
            OPEN.push(s);
          }
          else{
            s->setAlgCost(distance);
//remove From Queue (c)
            auto it = find(OPEN.c.begin(), OPEN.c.end(), s);
            if (it != OPEN.c.end()) {
              OPEN.c.erase(it);
              make_heap(OPEN.c.begin(),OPEN.c.end(), OPEN.comp);
            }
            //when node enters to priority queue it updates the heap
            OPEN.push(s);
          }
        }
      }
    }
    return "false";
  }

//return the trace to the state
  vector<State<T> *> backTrace(State<T>* n,Searchable<T> *searchObj){
    list<State<T> *> pathLst;
    State<T> nxt=n;
    if(nxt!=NULL) {
      pathLst.insert(nxt);
    }
    while (nxt!=searchObj->getInitialState())
    {
      nxt= nxt.getFather();
      pathLst.insert(nxt);
    }
    return searchObj->createSolution(pathLst);
  }
//check if state is at the vector
  bool isExistClosed(State<T>* state,Searchable<T> *searchObj){
    for(auto s:CLOSED){
      if(searchObj->isEqual(s,state)){
        return true;
      }
    }
    return false;
  }
//check if state is at the queue
  bool isExistOPEN(State<T>* state,Searchable<T> *searchObj){
    for(auto s:OPEN){
      if(searchObj->isEqual(s,state)){
        return true;
      }
    }
    return false;
  }


};

#endif //EX4__BESTFS_H_
