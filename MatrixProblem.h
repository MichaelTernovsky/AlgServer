//
// Created by michael on 16/01/2020.
//

#ifndef EX4__MATRIXPROBLEM_H_
#define EX4__MATRIXPROBLEM_H_

#include "Searchable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;
template<typename T>
class MatrixProblem : public Searchable<T> {
 private:
  string matrixStr;
  int colsNum;
  int rowNum;
  vector<vector<int> > matrixVct;

 public:
  /**
   * CTOR
   * @param str
   */
  MatrixProblem(string str) {
    this->matrixStr = str;
    this->rowNum = this->getNumRows();
    this->colsNum = this->getNumCols();
    this->creatingMatrixVector();
  }

  /**
   * getNumRows - returning the number of rows in the matrix.
   * @return int - the number of rows.
   */
  int getNumRows() {
    string tmp = this->matrixStr;
    int nCounter = 0;
    int tmpLen = tmp.length();

    for (int k = 0; k < tmpLen; k++) {
      if (tmp[k] == '\n')
        nCounter++;
    }
    return nCounter - 2;
  }

  /**
 * getNumCols - returning the number of cols in the matrix.
 * @return int - the number of cols.
 */
  int getNumCols() {
    string tmp = this->matrixStr;
    int i = 0;
    int countRows = 0;

    while (tmp[i] != '\n') {
      if (tmp[i] != ',')
        countRows++;
      i++;
    }
    return countRows;
  }

  /**
   * creatingMatrixVector - the function creates the matrix from the str field.
   */
  void creatingMatrixVector() {
    string tmp = this->matrixStr;
    vector<int> vect;
    stringstream s(tmp);

    for (int j = 0; j < this->rowNum; j++) {
      // creating the vector - each col of the matrix
      for (int i; s >> i;) {
        vect.push_back(i);
        if (s.peek() == ',')
          s.ignore();
        if (s.peek() == '\n')
          break;
      }

      // filling the rows of the matrix
      this->matrixVct.push_back(vect);
      vect.clear();
    }
  }

  State<T> getInitialState() {
    cout << "initialState@#R%@#%@" << endl;
  };
  bool isGoalState(State<T> *st) {
    cout << "goalState@#R%@#%@" << endl;
  };
  State<T> *getAllPossibleStates(State<T> *st) {
    cout << "getAllPossibleStates@#R%@#%@" << endl;
  };
};

#endif //EX4__MATRIXPROBLEM_H_