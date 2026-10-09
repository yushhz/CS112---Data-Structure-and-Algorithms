// Node.h - Generic node class
// Holds one item of any data type and a pointer to the next node in the list.

#ifndef NODE_H
#define NODE_H

#include <cstddef>

// Generic node: holds any data type plus a pointer to the next node.
template <class T>
class Node
{
private:
  T data;
  Node<T> *next;

public:
  Node(const T &value) : data(value), next(NULL) {}

  T &getData() { return data; }
  const T &getData() const { return data; }
  Node<T> *getNext() const { return next; }
  void setNext(Node<T> *n) { next = n; }
};

#endif