#pragma once
#include "tile.h"
#include <vector>
#include "framework.h"
#include "AstartFinder.h"
#include <array>
#include <string>
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
		obstacle,
		route
	};
public:
	Map()
	{
		tiles.resize(tileCOL * tileROW);
		tiles.resize( tileCOL * tileROW );
		for (int y = 0; y < tileCOL; y++)
		{
			for (int x = 0; x < tileROW; x++)
			{
				int i = tileROW * y + x;
				tiles[i] = { x * tileSize, y * tileSize };
			}
		}
	}
	void Draw(HDC hdc)
	{
		for (int i = 0; i < tileROW * tileCOL; i++)
		{
			tiles[i].DrawTile(hdc);
			DrawInform( hdc, i );
		}
	}

	void DrawInform( HDC hdc, int i ) const
	{
		const int x = (i % tileROW);
		const int y = (i / tileROW);
		const auto c = finder.GetCell( { x, y } );
		const std::wstring fStr = std::to_wstring( c.f );
		const std::wstring gStr = std::to_wstring( c.g );
		const std::wstring hStr = std::to_wstring( c.h );
		TextOut( hdc, x * tileSize + 10, y * tileSize + 5, gStr.c_str(), (int)gStr.size() );
		TextOut( hdc, x * tileSize + tileSize - 20, y * tileSize + 5, hStr.c_str(), (int)hStr.size() );
		TextOut( hdc, x * tileSize + 20, y * tileSize + tileSize - 20, fStr.c_str(), (int)fStr.size() );
	}
	
	void Checkmouse(HDC hdc,const Vec2<int>& pos)
	{
		for (int i = 0; i < 90; i++)
		{
			if (tiles[i].InTile(pos))
			{
				SelectObject(hdc, CreateSolidBrush(RGB(0,0, 255)));
				tiles[i].DrawTile(hdc);
				DrawInform( hdc, i );
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
				DrawInform( hdc, i );
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
				DrawInform( hdc, i );
				int x = pos.x / 50;
				int y = pos.y / 50;
				grid[x][y] = (int)tileState::obstacle;
			}
		}
	}
	void Find()
	{
		finder.aStarSearch( grid, start, target );
  		GetResult();
	}
	void GetResult()
	{
		std::vector<Vec2<int>> p;
		p = finder.getPath(); //result ÁÂÇ¥°ª
		for (const Vec2<int>& e : p)
		{
			grid[e.y][e.x] = (int)tileState::route;
		}
		
	}
	void DrawResult(HDC hdc)
	{
		for (int y = 0; y < tileCOL; y++)
		{
			for (int x = 0; x < tileROW; x++)
			{
				if (grid[y][x] == (int)tileState::route)
				{
					SelectObject( hdc, CreateSolidBrush( RGB( 255, 0, 123 ) ) );
					tiles[tileROW*y+x].DrawTile( hdc ); 

					DrawInform( hdc, tileROW * y + x );
				}
			}
		}
	}

	void ResetAll()
	{
		finder.Reset();
		grid = {
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0}}
		};
	}
	
public:
	std::vector<std::vector<int>> grid =
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
		{{0,0,0,0,0,0,0,0,0,0}},
		{{0,0,0,0,0,0,0,0,0,0}}
	}
	};

private:
	static constexpr int tileROW = 10;
	static constexpr int tileCOL = 10;
	const int tileSize = Tile::getlength();

	std::vector<Tile> tiles;
	AstartFinder finder = { tileROW,tileCOL };
	  
	Vec2<int> start;
	Vec2<int> target;
};

