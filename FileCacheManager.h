//
// Created by michael on 09/01/2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_

#include "CacheManager.h"
#include "Solver.h"

template<typename P, typename S>
class FileCacheManager : public CacheManager<P, S> {
 private:
  unsigned int _capacity;
  unordered_map<P, typename list<ObjectData<P, S>>::iterator> _cache;
  list<ObjectData<P, S>> _lst;
  hash<string> haser; // hash table that helps us to know the files object name

 public:
  FileCacheManager(int capacity);
  void insert(P key, S obj);
  void writeToDisk(S *obj, string fileName);
  int isExist(P key);
  S get(P key);
};

template<typename P, typename S>
FileCacheManager<P, S>::FileCacheManager(int capacity) {
  _capacity = capacity;
}

template<typename P, typename S>
void FileCacheManager<P, S>::writeToDisk(S *obj, string fileName) {
  fstream out(fileName, ios::out | ios::binary);
  if (out.is_open()) {
    out << *obj;
  } else {
    throw "Could not open the file";
  }
  out.close();
}

template<typename P, typename S>
void FileCacheManager<P, S>::insert(P key, S obj) {

  //creating new file name according to the hashing
  int hashed = this->haser(key);
  string fileName = to_string(hashed);
  fileName += ".txt";

  bool limitSizeFlag = false;
  if (_cache.size() + 1 > _capacity) {
    limitSizeFlag = true;
  }
  // the object was not found in cache
  if (_cache.find(key) == _cache.end()) {
    // we are reaching the limit
    if (limitSizeFlag) {
      string keyToDelete = _lst.back().getDataKey();
      auto itr = _cache.find(keyToDelete);
      _lst.erase(itr->second);
      _cache.erase(keyToDelete);
    }

    fstream out(fileName, ios::out | ios::binary);
    if (out.is_open()) {
      ObjectData<P, S> objData(key, obj);

      _lst.push_front(objData);
      _cache[key] = _lst.begin();

      writeToDisk(&obj, fileName);
    }
  } else {
    // the object was found
    auto itr = _cache.find(key);
    _lst.erase(itr->second);
    _cache.erase(key);

    ObjectData<P, S> objData(key, obj);
    _lst.push_front(objData);
    _cache[key] = _lst.begin();

    writeToDisk(&obj, fileName);
  }
}

template<typename P, typename S>
S FileCacheManager<P, S>::get(P key) {

  S getObj;

  int hashed = this->haser(key);
  string fileName = to_string(hashed);
  fileName += ".txt";

  // if the object is not found on cache
  if (_cache.find(key) == _cache.end()) {
    fstream in(fileName, ios::in | ios::binary);
    // the object was not found in files also - it is a new object
    if (!in.is_open()) {
      cout << "Object was not found" << endl;
    } else {
      // read the object from the files
      in >> getObj;
      in.close();

      // writing the object to the map and list
      bool limitSizeFlag = false;
      if (_cache.size() + 1 > _capacity) {
        limitSizeFlag = true;
      }

      // we are reaching the limit
      if (limitSizeFlag) {
        string keyToDelete = _lst.back().getDataKey();
        auto itr = _cache.find(keyToDelete);
        _lst.erase(itr->second);
        _cache.erase(keyToDelete);
      }
      ObjectData<P, S> objData(key, getObj);
      _lst.push_front(objData);
      _cache[key] = _lst.begin();
    }
  } else {
    // return the object from the cache
    auto itr = _cache.find(key);
    getObj = (itr->second)->getDataObj();

    // deleting the current object from the cache
    _lst.erase(itr->second);
    _cache.erase(key);

    // entering the new object to the cache instead of the old one
    ObjectData<P, S> objData(key, getObj);
    _lst.push_front(objData);
    _cache[key] = _lst.begin();
  }
  return getObj;
}

template<typename P, typename S>
int FileCacheManager<P, S>::isExist(P key) {
  if (_cache.find(key) != _cache.end()) {
    // found in the cache
    return 1;
  } else {
    // trying to get the object from the disk
    int hashed = this->haser(key);
    string fileName = to_string(hashed);
    fileName += ".txt";
    fstream in(fileName, ios::in | ios::binary);
    if (!in.is_open()) {
      // object not found on disk
      return 0;
    } else {
      // object found on disk
      return 1;
    }
  }
}

#endif //EX4__FILECACHEMANAGER_H_