//
// Created by michael on 09/01/2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "Solver.h"
#include "CacheManager.h"
#include "Server.h"
#include "AlgServer.h"
using namespace server_side;

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler {
 private:
  Solver<P, S> *s; // P - problem and S - solution
  CacheManager<P, S> *ch;
 public:
  MyTestClientHandler(Solver<P, S> *s, CacheManager<P, S> *ch);
  void handleClient(InputStream *input_stream, OutPutStream *out_put_stream);
};

/**
 * CTOR
 * @param s - the solver
 * @param ch - the cache manager
 */
template<typename P, typename S>
MyTestClientHandler<P, S>::MyTestClientHandler(Solver<P, S> *s, CacheManager<P, S> *ch) {
  this->s = s;
  this->ch = ch;
}

/**
 * handleClient
 * @param input_stream
 * @param out_put_stream
 */
template<typename P, typename S>
void MyTestClientHandler<P, S>::handleClient(InputStream *input_stream, OutPutStream *out_put_stream) {
  // reading the problem from the input
  P problem = input_stream->readFromStream(); // get the problem from the input

  S solution;

  if (problem == "end") // need to close the socket
    return;

  if (this->ch->isExist(problem) == 1) {
    // if the solution is available - return it
    cout << "we found the object in cache/disk" << endl;
    solution = this->ch->get(problem);
  } else {
    // create the solution
    solution = this->s->solve(problem);
    // insert the new solution into the cache manager
    cout << "new solution" << endl;
    this->ch->insert(problem, solution);
  }

  // writing the solution to the output
  out_put_stream->writeToStream(solution);
}

#endif //EX4__MYTESTCLIENTHANDLER_H_