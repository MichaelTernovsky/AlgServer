//
// Created by michael on 09/01/2020.
//

#include "StringReverser.h"

string StringReverser::solve(string str) {
  int n = str.length();
  string newStr = str;

  for (int i = 0; i < n / 2; i++)
    swap(newStr[i], newStr[n - i - 1]);

  return newStr;
}