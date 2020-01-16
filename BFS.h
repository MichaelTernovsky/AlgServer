//
// Created by michael on 16/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include "Searcher.h"
#include <iostream>
using namespace std;

template<typename T>
class BFS : public Searcher<T> {

  template<typename S>
  S search(Searchable<T> searchObj) {
    cout << "moshe" << endl;
  }

};

#endif //EX4__BFS_H_
