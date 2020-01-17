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
  vector<vector<T> > matrixVct;

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

    while (tmp[i] != '\n' && tmp[i] != '\r') {
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
    vector<T> vect;
    stringstream s(tmp);

    for (int j = 0; j < this->rowNum; j++) {
      // creating the vector - each col of the matrix
      for (int i; s >> i;) {
        vect.push_back(i);
        if (s.peek() == ',')
          s.ignore();
        if (s.peek() == '\n' || s.peek() == '\r')
          break;
      }

      // filling the rows of the matrix
      this->matrixVct.push_back(vect);
      vect.clear();
    }
  }

  /**
   * getInitialState - the function returns the initial state of the matrix.
   * @return State<T> * - the initial state.
   */
  State<T> *getInitialState() {
    // running over the str and finding the starting point
    string tmp = this->matrixStr;
    vector<T> vect;
    stringstream s(tmp);

    for (int i; s >> i;) {
      vect.push_back(i);
      if (s.peek() == ',' || s.peek() == '\n')
        s.ignore();
    }

    int vctSize = vect.size();
    int i = vect[vctSize - 4];
    int j = vect[vctSize - 3];

    T val = this->matrixVct[i][j];

    State<T> *initState = new State<T>(i, j, val);
    return initState;
  };

  /**
 * isGoalState - the function returns the true if the state we get as parameter is the goal state
 * of the matrix.
 * @return bool - true if the state we get as parameter is the goal state of the matrix,
 * and false otherwise.
 */
  bool isGoalState(State<T> *st) {
    // running over the str and finding the goal point
    string tmp = this->matrixStr;
    vector<T> vect;
    stringstream s(tmp);

    for (int i; s >> i;) {
      vect.push_back(i);
      if (s.peek() == ',' || s.peek() == '\n')
        s.ignore();
    }

    int vctSize = vect.size();
    int i = vect[vctSize - 2];
    int j = vect[vctSize - 1];

    T val = this->matrixVct[i][j];

    State<T> *goalState = new State<T>(i, j, val);

    if (goalState->getValue() == -1) {
      std::cerr << "goal point is -1" << std::endl;
    }

    return st->isEqual(goalState);
  };

  /**
   * getAllPossibleStates - the function returns the neighbors of the state we get as parameter.
   * @param st - the state.
   * @return vector<State<T> *> - vector of neighbors.
   */
  vector<State<T> *> getAllPossibleStates(State<T> *st) {
    vector<State<T> *> vect;
    State<T> *state1 = NULL;
    State<T> *state2 = NULL;
    State<T> *state3 = NULL;
    State<T> *state4 = NULL;

    int i = st->getI();
    int j = st->getJ();

    if ((i == 0 && j == this->colsNum - 1)) {
      if (matrixVct[i][j - 1] != -1) state1 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i + 1][j] != -1) state2 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
    } else if (i == this->rowNum - 1 && j == 0) {
      if (matrixVct[i - 1][j] != -1) state1 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
      if (matrixVct[i][j + 1] != -1) state2 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
    } else if (i == 0 && j == 0) {
      if (matrixVct[i + 1][j] != -1) state1 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
      if (matrixVct[i][j + 1] != -1) state2 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
    } else if (i == 0 && j != 0) {
      if (matrixVct[i][j + 1] != -1) state1 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
      if (matrixVct[i][j - 1] != -1) state2 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i + 1][j] != -1) state3 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
    } else if (i != 0 && j == 0) {
      if (matrixVct[i + 1][j] != -1) state1 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
      if (matrixVct[i - 1][j] != -1) state2 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
      if (matrixVct[i][j + 1] != -1) state3 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
    } else if (i == this->rowNum - 1 && j == this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i - 1][j] != -1) state2 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
    } else if (i == this->rowNum - 1 && j != this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i][j + 1] != -1) state2 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
      if (matrixVct[i - 1][j] != -1) state3 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
    } else if (i != this->rowNum - 1 && j == this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i - 1][j] != -1) state2 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
      if (matrixVct[i + 1][j] != -1) state3 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
    } else {
      if (matrixVct[i - 1][j] != -1) state1 = new State<T>(i - 1, j, matrixVct[i - 1][j]);
      if (matrixVct[i][j - 1] != -1) state2 = new State<T>(i, j - 1, matrixVct[i][j - 1]);
      if (matrixVct[i + 1][j] != -1) state3 = new State<T>(i + 1, j, matrixVct[i + 1][j]);
      if (matrixVct[i][j + 1] != -1)state4 = new State<T>(i, j + 1, matrixVct[i][j + 1]);
    }

    if (state1 != NULL) vect.push_back(state1);
    if (state2 != NULL) vect.push_back(state2);
    if (state3 != NULL) vect.push_back(state3);
    if (state4 != NULL) vect.push_back(state4);

    return vect;
  };
};

#endif //EX4__MATRIXPROBLEM_H_