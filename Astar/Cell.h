#pragma once
#include "vec2.h"
#include <math.h>
class Cell
{
public:
	Cell()
		:
		parents(-1, -1),
		f(-1),
		g(-1),
		h(-1)
	{}
	double CalculateHvalue(const Vec2<int>& src, const Vec2<int>& dest)
	{
		return sqrt((src.x - dest.x)* (src.x - dest.x) + 
			(src.y - dest.y) * (src.y - dest.y));
	}
	bool isDestination( Vec2<int>& position, Vec2<int>& dest)
	{
		if (position == dest)
		{
			return true;
		}
		return false;
	}
private:
	Vec2<int> parents;
	double f, g, h;
};

