#include "dynamic_array_list.hpp"
#include <stdexcept>

//Helper method to grow the array when the size is equal to the count
template <typename T>
void DynamicArrayList<T>::grow()	
{
	T *temp = dynamicArray;
	
	dynamicArray = new T[size*2];
	
    for ( int i=0;i<count; i++ )
        dynamicArray[i] = temp[i];
		
    delete [] temp;
	temp = nullptr;
	
	size = size*2;
}

//Default constructor that initializes an array
//of type T and size 1
template <typename T>
DynamicArrayList<T>::DynamicArrayList()
{
  size = 1;
  count = 0;
  dynamicArray = new T[size];
}

//Destructor to deallocate the memory stored by the array
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
  delete [] dynamicArray;
}

//The copy constructor to copy the data from
//a list x and put it into our new instance of a list
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T> & x)
{
  size = x.size;
  count = x.count;
  dynamicArray = new T[size];
  for (int i = 0; i < count; i++)
	dynamicArray[i] = x.dynamicArray[i];
}

//The assignment operator to copy the data from
//a list x and put it into our list
template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(const DynamicArrayList<T> & x)
{
	if(this != &x)
	{
		size = x.size;
		count = x.count;
		dynamicArray = new T[size];
		for (int i = 0; i < count; i++)
			dynamicArray[i] = x.dynamicArray[i];
	}
  return *this;
}

//Returns if the list has no entries
template <typename T>
bool DynamicArrayList<T>::isEmpty() const noexcept
{
  return (count == 0);
}

//Returns the number of entries in the list
template <typename T>
std::size_t DynamicArrayList<T>::getLength() const noexcept
{
  return count;
}

//Creates a hole at the point of insertion
//and moves all data at that point back to insert the new
//item into that position. Calls grow if the array is full.
template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
  bool ableToInsert = (position >= 0) && (position <= count);
  
  if (ableToInsert)
  {
  
		if (count == size) grow();
		
		for ( int i=count; i>position; i-- )
			dynamicArray[i] = dynamicArray[i-1];
		
		dynamicArray[position] = item;
		count++;
  }
  else
	throw std::range_error("Unable to insert");
  
  
}

//Removes the entry from and index and slides the rest
//of the entries down to fill the hole
template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
	bool ableToRemove = (position >= 0) && (position < count);
	
	if (ableToRemove)
	{
		for (int i = position; i < count - 1; i++)
			dynamicArray[i] = dynamicArray[i+1];
			
		count --;
	}
	else
		throw std::range_error("Unable to remove");
	
}

//clears all data from the array
template <typename T>
void DynamicArrayList<T>::clear() noexcept
{
	for  (int i = count - 1; i >= 0; i++)
		remove(i);
  
  size = 0;
  count = 0;
}

//Returns the entry at the specified index
template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position) const
{
	bool ableToGet = (position >= 0) && (position < count);
	
	if (ableToGet)
		return dynamicArray[position];
	else
	{
		throw std::range_error("Unable to get");
	}
	
}

//Changes the value at the specified index
//to a new value
template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
    bool ableToSet = (position >= 0) && (position < count);
	
	if (ableToSet)
		dynamicArray[position] = newValue;
	else
	{
		throw std::range_error("Unable to set");
	}
}


