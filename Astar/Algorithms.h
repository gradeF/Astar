#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"
#include "vec2.h"
class Algorithms
{
public:
	Algorithms()
	{

	}

	int Search()
	{
		//if list is not empty
		//find node least f value put it at q
		//q = least f
		//pop q in the openlist
		//make 8 successor their parent to q	
		// >>for
		//for each successor
		//if successor is goal, stop searching
		//else compute h and g for successor
		//successor.g = q.g + distance of successor and q
		//successor.h = distance of destination to successor
		//successor.h = successor.g + successor.h

		//if a node with the same position as successor is in
		//the open list which has a lower f than successor, skip
		//this successor

		//if a node with the same position as successor is in the
		//Closed list which has a lower f than successor, skip
		//this successor, add the node to the open list
		//end(for loop)
		//<<for

		//push q on the closed list
		//end(while loop)
		//<<while
	}

private:
	std::vector<int> openlist;
	std::vector<int> closelist;
	std::vector<int> successor; //We need 8 successor succesor's parents is q.
	Vec2<int> startPos;
	Vec2<int> desPos;
	int q;
};

