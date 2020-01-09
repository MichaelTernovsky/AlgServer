//
// Created by michael on 09/01/2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_

using namespace std;
#include <iostream>

// Interface
class ClientHandler {
 public:
  void handleClient(ifstream input, ofstream output);
};

#endif //EX4__CLIENTHANDLER_H_