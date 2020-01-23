#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_

using namespace std;
#include "Solver.h"
#include <string>

class StringReverser : public Solver<string, string> {
 public:
  string solve(string str);
};

#endif //EX4__STRINGREVERSER_H_