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
#include <mutex>

using namespace server_side;

template<typename P, typename S>
class MyClientHandler : public ClientHandler {
 private:
  Solver<P, S> *s; // P - problem and S - solution
  CacheManager<P, S> *ch;
  mutex locker;

 public:
  MyClientHandler(Solver<P, S> *s, CacheManager<P, S> *ch);
  void handleClient(InputStream *input_stream, OutPutStream *out_put_stream);
  bool endsWith(string s1, string s2);
  MyClientHandler<P, S> *createClone();
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

template<typename P, typename S>
bool MyClientHandler<P, S>::endsWith(string s1, string s2) {
  int n1 = s1.length(), n2 = s2.length();
  if (n1 > n2)
    return false;
  for (int i = 0; i < n1; i++)
    if (s1[n1 - i - 1] != s2[n2 - i - 1])
      return false;
  return true;
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

  string endStr1 = "end\r\n";
  string endStr2 = "end\n";
  string endStr3 = "end\r";
  string endStr4 = "end\n\r";
  string endStr5 = "end";

  string tmp = input_stream->readFromStream();

  while (!endsWith(endStr1, tmp) && !endsWith(endStr2, tmp) && !endsWith(endStr3, tmp) && !endsWith(endStr4, tmp)
      && !endsWith(endStr5, tmp)) {
    str += tmp;
    tmp = input_stream->readFromStream();
  }

  locker.lock();
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
  locker.unlock();
}

template<typename P, typename S>
MyClientHandler<P, S> *MyClientHandler<P, S>::createClone() {
  return new MyClientHandler<P, S>(this->s->createClone(), this->ch);
}

#endif //EX4__MYCLIENTHANDLER_H_
