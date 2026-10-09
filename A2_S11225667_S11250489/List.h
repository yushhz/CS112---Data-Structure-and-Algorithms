// List.h - Generic singly linked list class
// Manages a chain of Node objects and works with any data type.
// Supports adding to the end, getting an item by position, searching,
// and clearing. Nodes are freed automatically by the destructor.

#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include "Node.h"

// Generic singly linked list. Works with any type T that supports
// copy-construction and operator== (needed only for search()).
template <class T>
class List
{
private:
  Node<T> *head;
  Node<T> *tail;
  int count;

  // Copying is disabled so two lists never share (and double-delete) nodes.
  List(const List<T> &other);
  List<T> &operator=(const List<T> &other);

public:
  List() : head(NULL), tail(NULL), count(0) {}

  ~List() { clear(); }

  bool isEmpty() const { return count == 0; }
  int size() const { return count; }

  // Adds a value to the end of the list.
  void insertAtEnd(const T &value)
  {
    Node<T> *n = new Node<T>(value);
    if (head == NULL)
    {
      head = tail = n;
    }
    else
    {
      tail->setNext(n);
      tail = n;
    }
    count++;
  }

  // Returns a reference to the element at the given index (0-based).
  // The caller must make sure 0 <= index < size().
  T &getAt(int index) const
  {
    Node<T> *cur = head;
    for (int i = 0; i < index; i++)
    {
      cur = cur->getNext();
    }
    return cur->getData();
  }

  // Returns a pointer to the first element equal to key, or NULL.
  T *search(const T &key) const
  {
    Node<T> *cur = head;
    while (cur != NULL)
    {
      if (cur->getData() == key)
      {
        return &cur->getData();
      }
      cur = cur->getNext();
    }
    return NULL;
  }

  // Deletes every node, leaving an empty list.
  void clear()
  {
    while (head != NULL)
    {
      Node<T> *temp = head;
      head = head->getNext();
      delete temp;
    }
    tail = NULL;
    count = 0;
  }
};

#endif