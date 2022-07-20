#pragma once
#include "framework.h"
#include "vec2.h"
class Tile
{

public:
	Tile()
		:
		x(0),
		y(0),
		width( 50 ),
		height( 50 )
	{}
	void DrawTile(HDC hdc) const
	{
		for (int i = 0; i <10; i++)
		{
			for(int j = 0; j<9;j++)
			Rectangle( hdc, (width*i), (height*j), (width*i) + width, (height*j) + height );
		}

	}
	void InputKeyButton(const Vec2<int>& position)
	{
		
	}
private:
	int x;
	int y;
	int width;
	int height;
};