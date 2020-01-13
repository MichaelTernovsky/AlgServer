//
// Created by ofir on 12/01/2020.
//

#ifndef EX4__SOCKSTREAMS_H_
#define EX4__SOCKSTREAMS_H_
#include "AlgServer.h"
#include <string.h>
#include "sys/socket.h"
#include <unistd.h>

bool SocketOutputStream::writeToStream(string str) {
  int isSend=0;
  const char* msg = str.c_str();
  isSend=write(this->socket,msg,strlen(msg));
  if(isSend<0){
    cout<<"Error during write a massage! "<<endl;
    return false;
  }
  return true;
}
//distractor///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Need to Update.
string SocketInputStream::readFromStream() {

}

#endif //EX4__SOCKSTREAMS_H_