#include "frontier_queue.hpp"
#include "state.hpp"


template <typename T>
bool frontier_queue<T>::empty()
{
	//returns true if the queue is empty
	return (count == 0);
}



template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{	
	//creates a new instance of a state with cost and heuristic
	State<T> newState(p,cost,heur);
	
	//increments the count and pushes the new state onto the end of the heap
    count++;
    heap.push_back(newState);
	
	//go through the parents of the new state and bubble up until the heap is correctly ordered
	//the parent should be the ceiling of position/2
    for (int pos = count-1; pos > 0; pos = std::ceil(pos/2)) 
	{
        int parentIndex = std::ceil(pos/2);
		//if the parents is greater than the sibling, bubble up
        if (heap[pos].getFCost() < heap[parentIndex].getFCost()) 
		{ 
            State<T> copyParent = heap[parentIndex];
			heap[parentIndex] = heap[pos];
			heap[pos] = copyParent;
        } 
		else 
		{ 
            return;
        }
    }
	
}


template <typename T>
State<T> frontier_queue<T>::pop()
{
	//returns the state with the lowest f cost (heap[0])
	State<T> returnState = heap[0];
   
   //takes the last element and overwrites the top one with it
    heap[0] = heap[count-1];
	//removes that bottom element
	heap.pop_back();
    count--;

    int pos = 0;
    bool done = false;
	
	//run the loop while the heap is not ordered properly (done)
    while (!done) 
	{
		//find the index of the left child and the right child
        int left = 2*pos + 1;
        int right = 2*pos + 2;
		
		//if the left child does not exist, done
        if (left >= count) 
		{ 
            done = true;
        } 
		else 
		{ 
            int current = pos; 
            std::size_t val = heap[pos].getFCost();
			//if the left child is less than the value at this position, bubble down
            if (heap[left].getFCost() < val) 
			{
                current = left;
                val = heap[left].getFCost();
            }
			//if the right child exists, check the fcost of that too
            if (right < count) 
			{ 
                if (heap[right].getFCost() < val) 
				{ 
                    current = right;
                    val = heap[right].getFCost();
                }
            }
			//if the heap is balanced, done
            if (current == pos) 
			{ 
                done = true;
            } 
			//if it is not balanced swap the two elements and change the position for the next iteration
			else 
			{ 
                swap(heap[pos],heap[current]);
                pos = current;
            }
        }
    }
	//return the removed state
    return returnState;
}


template <typename T>
bool frontier_queue<T>::contains(const T &p)
{
	//Run through each element and check if they have the value searching for
	for (int i = 0; i < count; i++)
	{
		if (heap[i].getValue() == p) return true;
	}
	return false;
}


template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
	
	bool updated = false;
	int counter = 0;
	//Run through each element in the heap and see if that item p exists
	for (int i = 0; i < count; i++)
	{
		if (heap[i].getValue() == p)
		{
			if (heap[i].getPathCost() > cost)
			{
				heap[i].updatePathCost(cost);
				updated = true;
				counter = i;
				break;
			}
		}
	}
	
	//if it exists and the cost is cheaper, bubble up as necessary
	if (updated = true)
	{
		for (int pos = counter; pos > 0; pos = std::ceil(pos/2)) 
		{
			int parentIndex = std::ceil(pos/2);
			if (heap[pos].getFCost() < heap[parentIndex].getFCost()) 
			{ 
				State<T> copyParent = heap[parentIndex];
				heap[parentIndex] = heap[pos];
				heap[pos] = copyParent;
			} 
			else 
			{ 
				return;
			}
		}
		
	
	}
	
	
}
