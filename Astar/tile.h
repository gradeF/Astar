#pragma once
#include "framework.h"
#include "vec2.h"
class Tile
{
public:
	Tile()
	{
		center = { 25,25 };
		width = 50;
		height = 50;
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, center.x - (width*0.5), (int)center.x-(height*0.5), (int)center.x + (width * 0.5), (int)center.x + (height * 0.5));
	}
private:
	Vec2<int> center;
	int width;
	int height;
};

