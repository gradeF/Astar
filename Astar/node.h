#pragma once
#include "vec2.h"
class Node
{
public:
	Node() 
	{
		pair = { -1,-1 };
	}
	Node(int x, int y)
		:
		pair(x, y)
	{}
public:
	Vec2<int> pair;
};
