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
#include "Map.h"
struct cell
	{
	Vec2<int> parent;
	float h, f, g;
	cell()
		:
		parent(-1, -1),
		f(-1),
		g(-1),
		h(-1)
	{}
	};
class AstartFinder
{
public:
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
		if (!isDestination(start, target))
		{
			return;
		}

		std::vector<std::vector<bool>> closedList;
		std::vector<std::vector<cell>> cellDetails;
		int i, j;
		i = start.x;
		j = start.y;
		cellDetails[i][j].f = 0.0f;
		cellDetails[i][j].g = 0.0f;
		cellDetails[i][j].h = 0.0f;
		cellDetails[i][j].parent = { i,j };

		std::priority_queue<tuple, std::vector<tuple>, std::greater<tuple>> openlist;

		openlist.emplace(0.0, i, j);

		while (!openlist.empty())
		{
			const tuple& p = openlist.top();
			i = std::get<1>(p);
			j = std::get<2>(p);

			openlist.pop();
			closedList[i][j] = true;
		}

		for (int add_x = -1; add_x <= 1; add_x++)
		{
			for (int add_y = -1; add_y <= 1; add_y++)
			{
				Vec2<int> neighbour(i + add_x, j + add_y);
				if (isValid(grid, neighbour))
				{
					if (isDestination(neighbour, target))
					{
						cellDetails[neighbour.x][neighbour.y].parent = { i,j };
						tracePath(cellDetails, target);
						return;
					}
					else if (!closedList[neighbour.x][neighbour.y] && isUnBlocked(grid, neighbour))
					{
						double hNew, gNew, fNew;
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHvalue(neighbour, target);
						fNew = gNew + hNew;

						if (cellDetails[neighbour.x][neighbour.y].f == -1 ||
							cellDetails[neighbour.x][neighbour.y].f > fNew)
						{
							openlist.emplace(fNew, neighbour.x, neighbour.y);
							cellDetails[neighbour.x][neighbour.y].g = gNew;
							cellDetails[neighbour.x][neighbour.y].h = hNew;
							cellDetails[neighbour.x][neighbour.y].f = fNew;
							cellDetails[neighbour.x][neighbour.y].parent = { i,j };
						}
					}
				}
			}
		}
	}
private:
	bool isValid(std::vector<std::vector<int>>& grid, Vec2<int>& position)
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
	bool isUnBlocked(std::vector<std::vector<int>>& grid, Vec2<int>& point)
	{
		return isValid(grid, point) && grid[point.x][point.y] == 5;
	}

	bool isDestination( Vec2<int>& position, Vec2<int>& target)
	{
		return position == target;
	}

	double calculateHvalue(Vec2<int>& src, Vec2<int>& dest)
	{
		return sqrt((src.x - dest.y) * (src.x - dest.y)
			+ (src.x - dest.y) * (src.x - dest.y));
	}

	void tracePath(std::vector<std::vector<cell>>& cell, const Vec2<int>& target)
	{
		std::stack<Vec2<int>> Path;

		int row = target.x;
		int col = target.y;
		Vec2<int> next_node = cell[row][col].parent;
		do
		{
			Path.push(next_node);
			next_node = cell[row][col].parent;
			row = next_node.x;
			col = next_node.y;
		} while (cell[row][col].parent != next_node);

		Path.emplace(row, col);
		while (!Path.empty())
		{
			Vec2<int> p = Path.top();
			Path.pop();
		}
	}

private:
	Vec2<int> position;
	typedef std::tuple<double, int, int> tuple;
	int row=0;
	int col=0;
};

