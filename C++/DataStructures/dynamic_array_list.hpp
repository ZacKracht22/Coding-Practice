

#ifndef _DYNAMIC_ARRAY_LIST_HPP_
#define _DYNAMIC_ARRAY_LIST_HPP_

#include <cstdlib>
#include "abstract_list.hpp"
#include <cstddef>

template <typename T>
class DynamicArrayList: public AbstractList<T>
{
private:

		std::size_t count;
        std::size_t size;
        T *dynamicArray;
		
		void grow();
	
	
public:

// default constructor
  DynamicArrayList();
  
  // copy constructor
  DynamicArrayList(const DynamicArrayList<T> & x);
    
  // destructor
  ~DynamicArrayList();
  
  // copy assignment
  DynamicArrayList& operator=(const DynamicArrayList<T> & x);
  
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



};

#include "dynamic_array_list.tpp"

#endif
