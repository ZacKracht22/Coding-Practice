#include "deque.hpp"

//This creates a new instance of a node
//initialzing the data of the node as the item d
template <typename T>
template <typename U>
Deque<T>::Node<U>::Node(const T &d) {
  data = d;
  prev = nullptr; //the new node has no links so prev and next are null
  next = nullptr;
}

//Default constructor makes the head and tail null because the deque is empty
//and the count is 0
template <typename T>
Deque<T>::Deque():head(nullptr), tail(nullptr), count(0)
{
   
}

//The copy constructor creates a new Deque instance using the information from the 
//deque x
template <typename T>
Deque<T>::Deque(const Deque<T> & x): head(nullptr), tail(nullptr)
{
	count = x.count;
	//if the copied deque is empty, return with just the head and tail being null
  if(x.isEmpty()) return;
  

  
  NodePtrType tempx = x.head;
  NodePtrType last = head;
  
  while(tempx != nullptr)
  {
	NodePtrType temp = new Node<T>(tempx->data);
	temp->prev = last;
	if(last) last->next = temp;
	if(!last) head = temp;
	
	last = temp;
	tempx = tempx->next;
  }
  
  tail = last;
}

//Deallocates the memory by popping off each node
template <typename T>
Deque<T>::~Deque()
{
   while(!isEmpty())
	popBack();
	
	head = nullptr;
	tail = nullptr;
}

//Used when a deque is set to equal another deque. Copies all the data from x into this deque
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T> & x)
{
	if (this != &x)
	{
	
	while(!this->isEmpty())
		this->popBack();
	
	this->head = nullptr;
	this->tail = nullptr;
	
	head = nullptr;
	tail = nullptr;
	count = x.count;
	
  
  NodePtrType tempx = x.head;
  NodePtrType last = head;
  
  while(tempx != nullptr)
  {
	NodePtrType temp = new Node<T>(tempx->data);
	temp->prev = last;
	if(last) last->next = temp;
	if(!last) head = temp;
	
	last = temp;
	tempx = tempx->next;
  }
  
  tail = last;
  }
  
  return *this;
}

//Returns true if the deque is empty (count = 0)
template <typename T>
bool Deque<T>::isEmpty() const noexcept
{
   return (count == 0);
}

//Adds a new item to the front of the deque
template <typename T>
void Deque<T>::pushFront(const T & item)
{
	//temp is a new node pointer
   NodePtrType temp = new Node<T>(item);
   
   if(isEmpty())	//if the deque is empty, then temp will be the only node in the deque
   {
		head = temp;
		tail = temp;
   }
   else //if the deque is not empty, then the links have to be reordered to place temp at the front
   {
		temp->next = head;
		head->prev = temp;
		head = temp;
   }
   
   count++; //increment the counter of the deque
}

//Removed the front item from the deque
template <typename T>
void Deque<T>::popFront()
{
   if(isEmpty()) //if the deque is empty then nothing can be popped off
		throw std::runtime_error("The Deque is empty");
	else
	{
		NodePtrType deleteNode = nullptr;
		deleteNode = head;
		head = head->next;
		deleteNode->next = nullptr;
		delete deleteNode;
		deleteNode = nullptr;
		
		count--;
	}
}

//Returns the front item from the deque
template <typename T>
T Deque<T>::front() const
{
	//if the deque is empty then there is nothing to return
	if (isEmpty())
		throw std::runtime_error("The Deque is empty");
	else	
		return head->data;
}

//Adds an item to the back of the deque
template <typename T>
void Deque<T>::pushBack(const T & item)
{
	//temp is a new node to be placed on the back
   NodePtrType temp = new Node<T>(item);
   
   if(isEmpty()) //if the deque was empty, then temp will be the only item, having head and tail both point to it
   {
		head = temp;
		tail = temp;
   }
   else  //if it was not empty, reorder the tail links to add temp onto the back
   {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		
   }
   count++; //increment the deque counter
}

//Removes the last item from the deque
template <typename T>
void Deque<T>::popBack()
{
	//if the deque is empty then there is nothing to pop off
   if(isEmpty())
		throw std::runtime_error("The Deque is empty");
	else
	{
		NodePtrType deleteNode = nullptr;
		deleteNode = tail;
		tail = tail->prev;
		deleteNode->prev = nullptr;
		delete deleteNode;
		deleteNode = nullptr;
		
		count--;
	}
}

//Returns the last item from the deque
template <typename T>
T Deque<T>::back() const
{
	//if it is empty then there is nothing to return
   if (isEmpty())
		throw std::runtime_error("The Deque is empty");
	else	
		return tail->data;
}

template <class T>
void Deque<T>::swap(Deque<T> &x, Deque<T> &y) 
{
  std::swap(x.head, y.head);
  std::swap(x.tail, y.tail);
}