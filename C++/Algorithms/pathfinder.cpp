#include "image.h"
#include "deque.hpp"
#include <cstdlib>
#include <iostream>

#include <string>

#include <vector>

using namespace std;

struct State
{
	int row;
	int col;
};


int main(int argc, char *argv[])
{
	Deque<State> stateDeque;
	//Define a state for the starting position (R) and each direction you can move
	State R, left, right, up, down;
	
	//There must be 3 arguments for this program to work, returns failure if there isnt 3
	if (argc != 3) 
	{
		cerr << "Error: Two files are needed" << endl;
		return EXIT_FAILURE;
	}
	
	string inFile = argv[1];
	string outFile = argv[2];
	
	//Creates an image instance for the input picture, output picture, and an image to manipulate
	Image<Pixel> input = readFromFile(inFile);
	Image<Pixel> copyInput = readFromFile(inFile);

	//Runs through to make sure the images have the same pixels with exception for the green solution in the output
	int redCount = 0;
    for (intmax_t i = 0; i < input.width(); ++i)
	{
      for (intmax_t j = 0; j < input.height(); ++j) 
	  {
		if (input(i,j) != RED && input(i,j) != BLACK && input(i,j) != WHITE)
		{
			cerr << "Error: incorrect colors" << endl;
			return EXIT_FAILURE;
		}
		if (input(i,j) == RED)
		{
			redCount++;
			R.row = i;
			R.col = j;
			stateDeque.pushBack(R);
		}
      }
	}
	
	//if there is not one starting point, return failure
	if (redCount != 1)
	{
      cerr << "Error: There is not a single specified starting point.\n";
      return EXIT_FAILURE;
    }
	
	//Run the loop while there are states in the deque
	while(!stateDeque.isEmpty())
	{
		//if the front state is on the border, then return that as the solution
		if (stateDeque.front().row == 0 || stateDeque.front().row == input.width() - 1 || 
		stateDeque.front().col == 0 || stateDeque.front().col == input.height() - 1)
		{
			input(stateDeque.front().row, stateDeque.front().col).green = 255;
			input(stateDeque.front().row, stateDeque.front().col).alpha = 255;
			input(stateDeque.front().row, stateDeque.front().col).red = 0;
			input(stateDeque.front().row, stateDeque.front().col).blue = 0;
			
			writeToFile(input, outFile);

			cout << "Solution Found" << endl;
			return EXIT_SUCCESS;
		}
		
		//increment up down left and right state
		up.row = stateDeque.front().row - 1;
		up.col = stateDeque.front().col;
		
		down.row = stateDeque.front().row + 1;
		down.col = stateDeque.front().col;
		
		left.row = stateDeque.front().row;
		left.col = stateDeque.front().col - 1;
		
		right.row = stateDeque.front().row;
		right.col = stateDeque.front().col + 1;

		//Check for white spaces around the current location to add to the deque
		if(copyInput(down.row,down.col) == WHITE)
		{
			stateDeque.pushBack(down);
			copyInput(down.row,down.col) = BLACK;
		}
		if(copyInput(left.row,left.col) == WHITE)
		{
			stateDeque.pushBack(left);
			copyInput(left.row,left.col) = BLACK;
		}
		if(copyInput(up.row,up.col) == WHITE)
		{
			stateDeque.pushBack(up);
			copyInput(up.row,up.col) = BLACK;
		}
		if(copyInput(right.row,right.col) == WHITE)
		{
			stateDeque.pushBack(right);
			copyInput(right.row,right.col) = BLACK;
		}
		//set the front state to black and pop it off the deque
		copyInput(stateDeque.front().row,stateDeque.front().col) = BLACK;
		stateDeque.popFront();
	}
	//if no solution was found then return no solution
	if (stateDeque.isEmpty())
	{
		writeToFile(input, outFile);
		cout << "No Solution Found" << endl;
		return EXIT_SUCCESS;
	}
	
	
  
}

