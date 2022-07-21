#pragma once
#include "framework.h"
#include "vec2.h"
class Tile
{
public:
	Tile()
		:
		position(0,0)
		
	{}
	Tile(int x, int y)
		:
		position(x,y)
	{}
	void DrawTile(HDC hdc)
	{
		Rectangle(hdc, position.x, position.y, position.x +length, position.y +length);
	}
	static int getlength()
	{
		return length;
	}
	void SetPos(const Vec2<int>& pos)
	{
		position = pos;
	}
	bool InTile(const Vec2<int>& pos)
	{
		if (pos.x > position.x && pos.x < position.x + length&&
			pos.y>position.y && pos.y < position.y + length)
		{
			return true;
		}
		return false;
	}
private:
	Vec2<int> position; //starting points
	static constexpr int length = 50;
	
};