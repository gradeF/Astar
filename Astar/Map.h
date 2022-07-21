#pragma once
#include "tile.h"
#include <vector>
#include "framework.h"
class Map
{
public:
	enum class tileState
	{
		start,
		target,
		open,
		closed,
		obstacle
	};
public:
	Map()
	{
		tiles.resize(90);
		for (int y = 0; y < tileCOL; y++)
		{
			for (int x = 0; x < tileROW; x++)
			{
				int i = tileROW * y + x;
				tiles[i] = {x*tileSize, y*tileSize};
			}
		}
	}
	void Draw(HDC hdc)
	{
		for (int i = 0; i < tileROW * tileCOL; i++)
		{
			tiles[i].DrawTile(hdc);
		}
	}
	void Checkmouse(HDC hdc,const Vec2<int>& pos)
	{
		for (int i = 0; i < 90; i++)
		{
			if (tiles[i].InTile(pos))
			{
				SelectObject(hdc, CreateSolidBrush(RGB(0,0, 255)));
				tiles[i].DrawTile(hdc);
			}
		}
	}
	void Checkmouse2(HDC hdc, const Vec2<int>& pos)
	{
		for (int i = 0; i < 90; i++)
		{
			if (tiles[i].InTile(pos))
			{
				SelectObject(hdc, CreateSolidBrush(RGB(255,0 , 0)));
				tiles[i].DrawTile(hdc);
			}
		}
	}
	void Checkmouse3(HDC hdc, const Vec2<int>& pos)
	{
		for (int i = 0; i < 90; i++)
		{
			if (tiles[i].InTile(pos))
			{
				SelectObject(hdc, CreateSolidBrush(RGB(125, 125, 125)));
				tiles[i].DrawTile(hdc);
			}
		}
	}
private:
	static constexpr int tileROW = 10;
	static constexpr int tileCOL = 9;
	const int tileSize = Tile::getlength();

	std::vector<Tile> tiles;
};

