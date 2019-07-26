
#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include <cstdlib>
#include "abstract_list.hpp"
#include <cstddef>

//Includes the Node Class in order to 
//link the items in the list using pointers
template<class ItemType>
class Node
{
private:
	ItemType        item; // A data item
	Node<ItemType>* next; // Pointer to next node

public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const ;
	Node<ItemType>* getNext() const ;
}; // end Node


template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
		item(anItem), next(nextNodePtr)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
} 



template <typename T>
class LinkedList: public AbstractList<T>
{
public:

// default constructor
  LinkedList();
  
  // copy constructor
  LinkedList(const LinkedList<T> & x);
    
  // destructor
  ~LinkedList();
  
  // copy assignment
  LinkedList<T>& operator=(const LinkedList<T> & x);
  
  // determine if a list is empty
  bool isEmpty() const noexcept;

  // return current length of the list
  std::size_t getLength() const noexcept;

  // insert item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  void insert(std::size_t position, const T& item);

  // remove item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  void remove(std::size_t position);

  // remove all items from the list
  void clear() noexcept;

  // get a copy of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  T getEntry(std::size_t position) const;

  // set the value of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  void setEntry(std::size_t position, const T& newValue);

private:
	
	std::size_t count;
	Node<T>* headPtr;
	
	Node<T>* getNodeAt(size_t position) const;

};

#include "linked_list.tpp"

#endif