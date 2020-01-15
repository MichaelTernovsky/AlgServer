//
// Created by michael on 23/11/2019.
//

#ifndef EX2__CACHEMANAGER_H_
#define EX2__CACHEMANAGER_H_

using namespace std;
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>

// inner assisting class
template<typename P, typename S>
class ObjectData {
  P _key;
  S _obj;

 public:
  ObjectData(P key, S obj) : _key(key), _obj(obj) {}
  S getDataObj() { return _obj; }
  P getDataKey() { return _key; }
  ObjectData() {};
  ~ObjectData() {};
};

// interface
template<typename P, typename S>
class CacheManager {

 public:
  virtual void insert(P key, S obj) {};
  virtual void writeToDisk(S *obj, string fileName) {};
  virtual int isExist(P key) {};
  virtual S get(P key) {};
  virtual void addToHash(P problem) {};
};

#endif //EX2__CACHEMANAGER_H_