#ifndef __STACK_H__
#define __STACK_H__

#include<Jing/Collection.hh>
#include<Jing/List>
#include<Jing/Misc.hh>

namespace Jing{

template<class T>
class Stack:public Collection<T>{
protected:
  Jing::List<T> stk;

public:
//TODO:clear warnings
//TODO:equals method
//TODO:hashing
//TODO:classID dynamic infrastructure
//TODO:allow iterators to be used as insertion points
//TODO:Allow for multiple iterators
//TODO:remove character include
//TODO:remove iostream pieces and parts

//Constructors
  Stack();
  Stack(Collection<T>& c);
//Inserts
  void push(T& obj);
//  [inherited from collection]
  void insert(T& obj);
  void insertAll(Collection<T>& c);
//Removes
  T& pop();
  T& remove();
//  [inherited from collection]
  void remove(T& obj);
  void removeAll(Collection<T>& c);
//Contains
//  [inherited from collection]
  bool contains(T& obj) const;
  bool containsAll(Collection<T>& c) const;
//Reverse gets
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//Iterator
//  [inherited from Iterable]
  Iterator<T>& iterator() const;
//States
//  hash
//  [inherited from Object]
  unsigned long long hash() const;
//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
  Object* clone() const;
//  isempty
//  [inherited from collection]
  bool isEmpty() const;
//  size
//  [inherited from collection]
  size_t size() const;
//  clear
//  [inherited from collection]
  void clear();
};

}

#include"Stack.cc"

#endif

