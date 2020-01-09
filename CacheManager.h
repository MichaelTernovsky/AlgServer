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
template<typename T>
class ObjectData {
  string _key;
  T _obj;

 public:
  ObjectData(string key, T obj) : _key(key), _obj(obj) {}
  T getDataObj() { return _obj; }
  string getDataKey() { return _key; }
  ObjectData() {};
  ~ObjectData() {};
};

template<typename T>
class CacheManager {
  //unordered_map<string, pair<T, list<string>>> _cache;
  //unordered_map<string, std::pair<T, std::list<string>::iterator>> _cache;
  unsigned int _capacity;
  unordered_map<string, typename list<ObjectData<T>>::iterator> _cache;
  list<ObjectData<T>> _lst;

 public:
  CacheManager(int capacity);
  void insert(string key, T obj);
  void writeToDisk(T *obj, string fileName);
  int isExist(T object);
  T get(string key);
  void foreach(void (*func)(T &));
  ~CacheManager() {};
};

template<typename T>
CacheManager<T>::CacheManager(int capacity) {
  _capacity = capacity;
}

template<typename T>
void CacheManager<T>::writeToDisk(T *obj, string fileName) {
  fstream out(fileName, ios::out | ios::binary);
  if (out.is_open()) {
    out.write((char *) obj, sizeof(*obj));
  } else {
    throw "Could not open the file";
  }
  out.close();
}

template<typename T>
void CacheManager<T>::insert(string key, T obj) {

  //creating new file name according to the object and key
  string classType = T::class_name;
  string fileName = classType;
  fileName += key;

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
      ObjectData<T> objData(key, obj);

      _lst.push_front(objData);
      _cache[key] = _lst.begin();

      writeToDisk(&obj, fileName);
    }
  } else {
    // the object was found
    auto itr = _cache.find(key);
    _lst.erase(itr->second);
    _cache.erase(key);

    ObjectData<T> objData(key, obj);
    _lst.push_front(objData);
    _cache[key] = _lst.begin();

    writeToDisk(&obj, fileName);
  }
}

template<typename T>
T CacheManager<T>::get(string key) {

  T getObj;

  string classType = T::class_name;
  string fileName = classType;
  fileName += key;

  // if the object is not found on cache
  if (_cache.find(key) == _cache.end()) {
    fstream in(fileName, ios::in | ios::binary);
    // the object was not found in files also - it is a new object
    if (!in.is_open()) {
      throw "Object was not found";
    } else {
      // read the object from the files
      in.read((char *) &getObj, sizeof(getObj));
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
      ObjectData<T> objData(key, getObj);
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
    ObjectData<T> objData(key, getObj);
    _lst.push_front(objData);
    _cache[key] = _lst.begin();
  }
  return getObj;
}

template<typename T>
void CacheManager<T>::foreach(void (*func)(T &)) {
  for (auto itr = _cache.begin(); itr != _cache.end(); itr++) {
    T obj = (itr->second)->getDataObj();
    func(obj);
  }
}

template<typename T>
int CacheManager<T>::isExist(T key) {
  if (_cache.find(key) == _cache.end())
    return 0;
  else
    return 1; // the object was found
}

#endif //EX2__CACHEMANAGER_H_