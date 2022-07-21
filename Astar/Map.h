#pragma once
#include "tile.h"
#include <vector>
#include "framework.h"
#include "AstartFinder.h"
#include <array>
class Map
{
public:
	enum class tileState
	{
		normal,
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
				int x = pos.x / 50;
				int y = pos.y / 50;
				grid[x][y] = (int)tileState::start;
				start = { x,y };
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
				int x = pos.x / 50;
				int y = pos.y / 50;
				grid[x][y] = (int)tileState::target;
				target = { x,y };
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
				int x = pos.x / 50;
				int y = pos.y / 50;
				grid[x][y] = (int)tileState::obstacle;
			}
		}
	}
	void Find()
	{
		finder.aStarSearch(grid, start, target);
	}
	void ResultDraw()
	{
		for (int i = 0; i < tileROW * tileCOL; i++)
		{
			if()
		}
	}
private:
	std::array<std::array<int, 10>, 9> grid =
	{
	{
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}}
	}
	};

private:
	static constexpr int tileROW = 10;
	static constexpr int tileCOL = 9;
	const int tileSize = Tile::getlength();

	std::vector<Tile> tiles;
	AstartFinder finder;
	typedef std::pair<int, int> Pair;
	Pair start = {0,0};
	Pair target = { 0,0 };
	typedef std::tuple<double, int, int> Tuple;
};

