////
//// Created by michael on 16/01/2020.
////
//
//#ifndef EX4__BESTFS_H_
//#define EX4__BESTFS_H_
//
//#include "Searcher.h"
//#include <iostream>
//#include <queue>
//#include "State.h"
//#include <vector>
//#include <set>
//#include <iterator>
//
//using namespace std;
//
//template<typename T,typename S>
//class BestFS : public Searcher<T, S> {
//
//  priority_queue <State<T*>> OPEN;
//  vector<State<T> *>  CLOSED;
//  vector<State<T> *> path;
//
//  S search(Searchable<T> *searchObj) {
//    State<T> n;
//    OPEN.push(searchObj->getInitialState());
//    while (!OPEN.empty()){
//      n = OPEN.top(); //remove the best node from OPEN
//      OPEN.pop();
//      CLOSED.push(n); //we want to check n again.
//      if(searchObj->isGoalState(n)){
//        path = backTrace(n); ////////////////////////////////////////////////////////////////
//        return path; ///////////////////////////////////////////////////////////////////
//      }
//      vector<State<T> *> successors = searchObj->getAllPossibleStates(n);
//      for(State<T> * s:successors){
//        if(!this->isExistClosed(s)&&!this->isExistOPEN(s)){
//          s->setFather(n);
//          OPEN.push(s);
//        }
//        else{
//          if(!this->isExistOPEN(s)){
//            OPEN.push(s);
//          }
//          else{
//
//          }
//        }
//      }
//    }
//
//    cout << "moshe" << endl;
//    S obj;
//    return obj;
//  }
//
////return the trace to the state
//  vector<State<T> *> backTrace(State<T*>){
//    string path = "";
//    for(State<T> s:CLOSED){
//      path += s.getFather()
//      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    return path;
//  }
////check if state is at the vector
//  bool isExistClosed(State<T>* state,Searchable<T> *searchObj){
//    for(auto s:CLOSED){
//      if(searchObj->isEqual(s,state)){
//        return true;
//      }
//    }
//    return false;
//  }
////check if state is at the queue
//  bool isExistOPEN(State<T>* state,Searchable<T> *searchObj){
//    for(auto s:OPEN){
//      if(searchObj->isEqual(s,state)){
//        return true;
//      }
//    }
//    return false;
//  }
//
//  //show all the queue // need to change !
//  void showpq(priority_queue <int> gq)
//  {
//    priority_queue <int> g = gq;
//    while (!g.empty())
//    {
//      cout << '\t' << g.top();
//      g.pop();
//    }
//    cout << '\n';
//  }
//};
//
//#endif //EX4__BESTFS_H_
