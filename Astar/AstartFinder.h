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
class AstartFinder
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::tuple<double, int, int> Tuple;

	struct cell
	{
		Pair parent;
		int f, g, h;
		cell()
			:
			parent(-1, -1),
			f(-1),
			g(-1),
			h(-1)
		{}
	};

	

	template<size_t ROW, size_t COL>
	void aStarSearch(const std::array<std::array<int, COL>, ROW>& grid, const Pair& src, const Pair& dest)
	{
		if (!isValide(grid, src))
		{
			printf("Source is invalide\n");
			return;
		}

		if (isUnBlocked(grid, src) || isUnBlocked(grid, dest))
		{
			printf("Source or the destination is blocked\n");
			return;
		}

		if (isDestination(src, dest))
		{
			printf("We are already at the destination\n");
			return;
		}

		bool closedList[ROW][COL];
		memset(closedList, false, sizeof(closedList));

		std::array<std::array<cell, COL>, ROW> cellDetails;

		int i, j;
		i = src.first, j = src.second;
		cellDetails[i][j].f = 0.0;
		cellDetails[i][j].g = 0.0;
		cellDetails[i][j].h = 0.0;
		cellDetails[i][j].parent = { i,j };

		std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

		openList.emplace(0.0, i, j);

		while (!openList.empty())
		{
			const Tuple& p = openList.top();
			i = std::get<1>(p);
			j = std::get<2>(p);

			openList.pop();
			closedList[i][j] = true;

			for (int add_x = -1; add_x <= 1; add_x++)
			{
				for (int add_y = -1; add_y <= 1; add_y++)
				{
					Pair neighbour(i + add_x, j + add_y);
					if (isValide(grid, neighbour))
					{
						if (isDestination(neighbour, dest))
						{
							cellDetails[neighbour.first][neighbour.second].parent = { i,j };
							printf("The destination cell is found\n");
							tracePath(cellDetails, dest);
							return;
						}
						else if (!closedList[neighbour.first][neighbour.second] && isUnBlocked(grid, neighbour))
						{
							double gNew, hNew, fNew;
							gNew = cellDetails[i][j].g + 1.0;
							hNew = calculateHValue(neighbour, dest);
							fNew = gNew + hNew;
							if (cellDetails[neighbour.first][neighbour.second].f == -1 || cellDetails
								[neighbour.first][neighbour.second].f > fNew)
							{
								openList.emplace(fNew, neighbour.first, neighbour.second);
								cellDetails[neighbour.first][neighbour.second].g = gNew;
								cellDetails[neighbour.first][neighbour.second].h = hNew;
								cellDetails[neighbour.first][neighbour.second].f = fNew;
								cellDetails[neighbour.first][neighbour.second].parent = { i,j };
							}
						}
					}
				}
			}
		}
		printf("Failed to fine the Destination Cell\n");
	}
	std::vector<Pair> getPath() const
	{
		return Path;
	}
private:
	template<size_t ROW, size_t COL>
	bool isValide(const std::array<std::array<int, COL>, ROW>& grid, const Pair& point)
	{
		if (ROW > 0 && COL > 0)
		{
			if ((point.first >= 0) && (point.first < ROW)
				&& (point.second >= 0) && (point.second < COL))
			{
				return true;
			}
		}
		return false;
	}

	template<size_t ROW, size_t COL>
	bool isUnBlocked(const std::array<std::array<int, COL>, ROW>& grid, const Pair& point)
	{
		return isValide(grid, point) && grid[point.first][point.second] == 5;
	}

	bool isDestination(const Pair& position, const Pair& dest)
	{
		return position == dest;
	}

	double calculateHValue(const Pair& src, const Pair& dest)
	{
		return sqrt((src.first - dest.first) * (src.first - dest.first)
			+ (src.second - dest.second) * (src.second - dest.second));
	}

	template<size_t ROW, size_t COL>
	void tracePath(const std::array<std::array<cell, COL>, ROW>& cellDetails, const Pair& dest)
	{
		//printf("\nThe Path is");
		int row = dest.first;
		int col = dest.second;
		Pair next_node = cellDetails[row][col].parent;
		do {
			Path.push_back(next_node);
			next_node = cellDetails[row][col].parent;
			row = next_node.first;
			col = next_node.second;
		} while (cellDetails[row][col].parent != next_node);

		Path.emplace_back(row, col);
		while (!Path.empty())
		{
			Pair p = Path.back();
			//Path.pop();
			//printf("-> (%d, %d)", p.first, p.second);
		}
	}
private:
	std::vector<Pair> Path;
};

