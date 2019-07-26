#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstdlib>

#include "abstract_deque.hpp"

#include <cstddef>

template <typename T>
class Deque: public AbstractDeque<T>{

  private:
  
 
  void swap(Deque<T> & x, Deque<T> & y);

  
  template <class U>
  struct Node
  {
    U data;
    Node<U> * prev;
    Node<U> * next;

    Node(const T& d);
  };

  typedef Node<T>* NodePtrType;

  Node<T> * head;
  Node<T> * tail;
  int count;
  
  public:
  
  Deque();
  
  Deque(const Deque<T> & x);
  
  ~Deque();
  
  Deque<T>& operator=(const Deque<T> & x);
  
  /** Returns true if the deque is empty, else false
   */
  bool isEmpty() const noexcept;

  /** Add item to the front of the deque
   * may throw std::bad_alloc
   */
  void pushFront(const T & item);

  /** Remove the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
  void popFront();

  /** Returns the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
  T front() const;

  /** Add item to the back of the deque
   * may throw std::bad_alloc
   */
  void pushBack(const T & item);

  /** Remove the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
  void popBack();


  /** Returns the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
  T back() const;
  
};

#include "deque.tpp"

#endif
