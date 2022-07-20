#pragma once
#include <iostream>
#include <vector>
#include "node.h"
#include "vec2.h"
class Algorithms
{
public:
	Algorithms()
	{
		openlist = { 0,0 }; //startposition
		closelist = { 0,0 }; //closelist is empty;
		//put the starting node to openlist
	}
	int Search()
	{
		//if list is not empty
		if (!openlist.empty())
		{
			//find node least f value put it at q
			//q = least f
			q = node.f;
			while (true)
			{
				openlist.push_back(q);
				//pop q in the openlist
				//make 8 successor their parent to q
				for (int i = 0; i < sizeof(successor); i++)
				{
					if (successor[i]. == targetpos)
					{
						return 0;
					}
					else
					{
						successor[i].g = q.g + distance of successor and q;
						successor[i].h = Heuristics(successor, target);
						successor[i].f = successor[i].g + successor[i].h;
					}
					if (q in openlist && successor in openlist)
					{
						if (openlist.lower.f < successor)
						{
							skip this successor;
						}
					}
					if (q in closelist && successor in closelist)
					{
						if (closelist.lower.f < successor)
						{
							skip this successor;
							opelist.push_back(q);
						}
					}
				}
				closedlist.push_back(q);
			}
			
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
		
		
		
	}

private:
	std::vector<int> openlist;
	std::vector<int> closelist;
	std::vector<Node> successor; //We need 8 successor succesor's parents is q.
	int startpos;
	int targetpos;
	Node node;
	Node Successor[8];
	int q;
};

