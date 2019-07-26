#include "linked_list.hpp"
#include <stdexcept>

//A helper function to retrieve the node at
//a given index
template <typename T>
Node<T>* LinkedList<T>::getNodeAt(size_t position) const	
{
	
	 Node<T>* curPtr = headPtr;
	 for ( size_t i = 0; i < position; i++)        
		curPtr = curPtr->getNext(); 
		
		return curPtr;
	
}

//intialize the list with a count of 0 
//and a head pointer that points to nothing
template <typename T>
LinkedList<T>::LinkedList(): headPtr(nullptr), count(0)
{
}

//destructor to clear the list and deallocate memory
template <typename T>
LinkedList<T>::~LinkedList()
{
   clear(); 
}

//The copy constructor to copy the data from
//a list x and put it into our new instance of a list
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & x)
{
	count = x.count;
  Node<T>* origPtr = x.headPtr;
  
if (origPtr == nullptr ) headPtr =  nullptr;               
else
    {        
	      
	headPtr =  new Node<T>();        
	headPtr->setItem(origPtr->getItem()); 
              
	   Node<T>* newChainPtr = headPtr;      
               
	   while (origPtr != nullptr )        
	   { 
	             
	   origPtr = origPtr->getNext();     
          if(origPtr != nullptr)
		  {
		T nextItem = origPtr->getItem(); 
       
		Node<T>* newNodePtr =  new Node<T>(nextItem);
          
		newChainPtr->setNext(newNodePtr);  
         
		newChainPtr = newChainPtr->getNext();   
		}        
		}   
 
		newChainPtr->setNext( nullptr); 
	    
		}   
	   
}

//The assignment operator to copy the data from
//a list x and put it into our list
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & x)
{
	if(this != &x)
	{
			count = x.count;
  Node<T>* origPtr = x.headPtr;
  
if (origPtr == nullptr ) headPtr =  nullptr;               
else
    {        
	      
	headPtr =  new Node<T>();        
	headPtr->setItem(origPtr->getItem()); 
              
	   Node<T>* newChainPtr = headPtr;      
               
	   while (origPtr != nullptr )        
	   { 
	             
	   origPtr = origPtr->getNext();     
          if(origPtr != nullptr)
		  {
		T nextItem = origPtr->getItem(); 
       
		Node<T>* newNodePtr =  new Node<T>(nextItem);
          
		newChainPtr->setNext(newNodePtr);  
         
		newChainPtr = newChainPtr->getNext();   
			}        
		}   
 
		newChainPtr->setNext( nullptr); 
	    
		}   
		
	}
  return *this;
}

//Returns if the list is empty
template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return (count == 0);
}

//Returns the size of the list
template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return count;
}

//Inserts an item at a given index
//and pushes everything behind that location back
//one index
template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
  bool ableToInsert = (position >= 0) && (position <= count); 
  if (ableToInsert)    
  {
    
  Node<T>* newNode =  new Node<T>(item);

   if (position == 0)       
   {           
	      
		newNode->setNext(headPtr);           
		headPtr = newNode;       
	} 
	
	else 
    {           
	          
		Node<T>* prevPtr = getNodeAt(position - 1); 
                  
		 newNode->setNext(prevPtr->getNext());            
		 prevPtr->setNext(newNode);       
	}  
	
      count++;   
	  
	}
	
		else
			throw std::range_error("Unable to insert");
	  
}

//removes the entry at a given position
//and slides the rest of the entries down
template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  bool ableToRemove = (position >= 0) && (position < count); 
  
  if (ableToRemove)    
  {   
  
  Node<T>* remPtr =  nullptr ; 
  if (position == 0)       
  {            
            
  remPtr = headPtr; 

  headPtr = headPtr->getNext();
  } 
  
  else 
   {
	  
	   Node<T>* prevPtr = getNodeAt(position - 1); 
                    
		remPtr = prevPtr->getNext(); 
          
		prevPtr->setNext(remPtr->getNext());       
}   
      
remPtr->setNext( nullptr ); 
delete remPtr;       
remPtr =  nullptr ; 
count = count - 1;
	  }
		else
			throw std::range_error("Unable to remove");
 
}

//clears all entries in the list
template <typename T>
void LinkedList<T>::clear() noexcept
{
  while (!isEmpty())
	remove(0); 
headPtr = nullptr;
}

//Retrieves the entry of type T at a given index
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{

  bool ableToGet = (position >= 0) && (position < count);
  
  if (ableToGet)
  {
	 Node<T>* nodePtr = getNodeAt(position); 
	 return nodePtr->getItem(); 
  }
  else
	throw std::range_error("Unable to get");
  
}

//Changes the value of a given position to the new value
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  bool ableToSet = (position >= 0) && (position < count);
	
	if (ableToSet)
	{
		Node<T>* nodePtr = getNodeAt(position);
		nodePtr->setItem(newValue);
	}
	else
	{
		throw std::range_error("Unable to set");
	}
}

