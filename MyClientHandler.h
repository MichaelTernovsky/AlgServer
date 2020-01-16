//
// Created by michael on 16/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_

#include "Solver.h"
#include "CacheManager.h"
#include "Server.h"
#include "AlgServer.h"
#include "MatrixProblem.h"
using namespace server_side;

template<typename P, typename S>
class MyClientHandler : public ClientHandler {
 private:
  Solver<P, S> *s; // P - problem and S - solution
  CacheManager<P, S> *ch;
 public:
  MyClientHandler(Solver<P, S> *s, CacheManager<P, S> *ch);
  void handleClient(InputStream *input_stream, OutPutStream *out_put_stream);
};

/**
 * CTOR
 * @param s - the solver
 * @param ch - the cache manager
 */
template<typename P, typename S>
MyClientHandler<P, S>::MyClientHandler(Solver<P, S> *s, CacheManager<P, S> *ch) {
  this->s = s;
  this->ch = ch;
}

/**
 * handleClient
 * @param input_stream
 * @param out_put_stream
 */
template<typename P, typename S>
void MyClientHandler<P, S>::handleClient(InputStream *input_stream, OutPutStream *out_put_stream) {

  // reading the problem from the input
  S solution;
  string str = "";

  string tmp = input_stream->readFromStream();
  while (tmp != "end\r\n") {
    str += tmp;
    tmp = input_stream->readFromStream();
  }

  // creating the matrix from the string we get from the client

  if (this->ch->isExist(str) == 1) {
    // if the solution is available - return it
    cout << "we found the object in cache/disk" << endl;
    solution = this->ch->get(str);
  } else {
    // create the solution
    solution = this->s->solve(str);
    // insert the new solution into the cache manager
    cout << "new solution" << endl;
    this->ch->insert(str, solution);
  }

  // writing the solution to the output
  out_put_stream->writeToStream(solution);
}

#endif //EX4__MYCLIENTHANDLER_H_
