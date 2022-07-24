#pragma once
#include <math.h>
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include "vec2.h"

class AstartFinder
{
public:
	struct cell
	{
		Vec2<int> parent;
		int h, f, g;
		cell()
			:
			parent(-1, -1),
			f(-1),
			g(-1),
			h(-1)
		{}
	};
public:
	AstartFinder(int row, int col)
		:
		row(row),
		col(col),
		cellDetails(row)
	{
		for (int k = 0; k < row; k++)
		{
			cellDetails[k].resize( col );
		}
	}
	void aStarSearch(std::vector<std::vector<int>>& grid, Vec2<int>& start, Vec2<int>& target)
	{
		if (!isValid(grid, start))
		{
			return;
		}
		if (!isUnBlocked(grid, start) && !isUnBlocked(grid, target))
		{
			return;
		}
		if (isDestination(start, target))
		{
			return;
		}

		startPos = start;

		std::vector<std::vector<bool>> closedList(row);
		for (int k = 0; k < row; k++)
		{
			closedList[k].resize(col);
		}
		Vec2<int> curPos = start;
		
		cellDetails[curPos.y][curPos.x].f = 0;
		cellDetails[curPos.y][curPos.x].g = 0;
		cellDetails[curPos.y][curPos.x].h = 0;
		cellDetails[curPos.y][curPos.x].parent = start;

		std::priority_queue<tuple, std::vector<tuple>, std::greater<tuple>> openlist;

		openlist.emplace(0, curPos.x, curPos.y);
		
		while (!openlist.empty())
		{
			const tuple& p = openlist.top();
			curPos = { std::get<1>( p ), std::get<2>( p ) };

			openlist.pop();
			closedList[curPos.y][curPos.x] = true;

			for (int dirX = -1; dirX <= 1; dirX++)
			{
				for (int dirY = -1; dirY <= 1; dirY++)
				{
					Vec2<int> neighbour( curPos.x + dirX, curPos.y + dirY );
					if (isValid( grid, neighbour ))
					{
						if (isDestination( neighbour, target ))
						{
							const int gNew = GetDistance( { start.x,start.y }, neighbour );
							const int hNew = GetDistance( neighbour, target );
							const int fNew = gNew + hNew;
							cellDetails[neighbour.y][neighbour.x].g = gNew;
							cellDetails[neighbour.y][neighbour.x].h = hNew;
							cellDetails[neighbour.y][neighbour.x].f = fNew;
							cellDetails[neighbour.y][neighbour.x].parent = curPos;
							tracePath( cellDetails, target );
							return;
						}
						else if (!closedList[neighbour.y][neighbour.x] && isUnBlocked( grid, neighbour ))
						{
							int hNew, gNew, fNew;
							
							gNew = GetDistance( { start.x,start.y }, neighbour );
							hNew = GetDistance( neighbour, target );
							fNew = gNew + hNew;

							if (cellDetails[neighbour.y][neighbour.x].f == -1 ||
								cellDetails[neighbour.y][neighbour.x].f > fNew)
							{
								openlist.emplace( fNew, neighbour.x, neighbour.y );
								cellDetails[neighbour.y][neighbour.x].g = gNew;
								cellDetails[neighbour.y][neighbour.x].h = hNew;
								cellDetails[neighbour.y][neighbour.x].f = fNew;
								cellDetails[neighbour.y][neighbour.x].parent = curPos;
							}
						}
					} 
				} 
			}
		}
	}

	std::vector<Vec2<int>> getPath() const
	{
		return Path;
	}

	auto GetCell( const Vec2<int>& pos ) const
	{
		return cellDetails[pos.y][pos.x];
	}

	void Reset()
	{
		Path.clear();
		cellDetails.clear();
		cellDetails.resize( row );
		{
			for (int k = 0; k < row; k++)
			{
				cellDetails[k].resize( col );
			}
		}
	}

private:
	bool isValid(const std::vector<std::vector<int>>& grid, const Vec2<int>& position) const
	{
		if (row > 0 && col > 0)
		{
			if (position.x >= 0 && position.x < row
				&& position.y >= 0 && position.y < col)
			{
				return true;
			}
			return false;
		}
	}
	bool isUnBlocked( const std::vector<std::vector<int>>& grid, const Vec2<int>& point) const
	{
		return isValid(grid, point) && grid[point.x][point.y] != 5;
	}

	bool isDestination(const Vec2<int>& position, const Vec2<int>& target) const 
	{
		return position == target;
	}

	int GetDistance(const Vec2<int>& src, const Vec2<int>& target)
	{
		int dx = abs(src.x - target.x);
		int dy = abs(src.y - target.y);
		if (dx > dy)
		{
			return 14 * dy + 10 * (dx - dy);
		}
		return 14 * dx + 10 * (dy - dx);
	}

	void tracePath(const std::vector<std::vector<cell>>& cell, const Vec2<int>& target)
	{
		Vec2<int> next_node = target;
		while (next_node != startPos)
		{
			Path.push_back( next_node );
			next_node = cell[next_node.y][next_node.x].parent;
		}
		Path.push_back( next_node );
	}



	
private:
	Vec2<int> position;
	typedef std::tuple<int, int, int> tuple;
	std::vector<Vec2<int>> Path;
	std::vector<std::vector<cell>> cellDetails;
	int row=0;
	int col=0;
	Vec2<int> startPos;
};

