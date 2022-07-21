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
	int ROW = 0;
	int COL = 0;

public:
	
	bool isValide( const std::vector<std::vector<int>>& grid, Pair& point )
	{
		if (ROW > 0 && COL > 0)
		{
			return (point.first >= 0) && (point.first < ROW)
				&& (point.second >= 0) && (point.second < COL);
		}
		return false;
	}
	
	bool isUnBlocked( const std::vector<std::vector<int>>& grid,  Pair& point )
	{
		return isValide( grid, point ) && grid[point.first][point.second] == 5;
	}
	bool isDestination( const Pair& position, const Pair& dest )
	{
		return position == dest;
	}
	double calculateHValue( const Pair& src, const Pair& dest )
	{
		return sqrt( (src.first - dest.first) * (src.first - dest.first)
			+ (src.second - dest.second) * (src.second - dest.second) );
	}
	template<size_t ROW, size_t COL>
	void tracePath( const std::vector<std::vector<int>>& cellDetails, const Pair& dest )
	{
		std::vector<Pair> Path;

		int row = dest.first;
		int col = dest.second;
		Pair next_node = cellDetails[row][col].parent;
		do
		{
			Path.push_back( next_node );
			next_node = cellDetails[row][col].parent;
			row = next_node.first;
			col = next_node.second;
		} while (cellDetails[row][col].parent != next_node);

		Path.emplace_back( row, col );
		while (!Path.empty())
		{
			Pair p = Path.top();
			Path.pop_back();
		}
	}
	template<size_t ROW, size_t COL>
	void aStarSearch( const std::vector<std::vector<int>>& grid, const Pair& src, const Pair& dest )
	{
		if (!isValide( grid, src ))
		{
			return;
		}
		if (!isUnBlocked( grid, src ) || !isUnBlocked( grid, dest ))
		{
			return;
		}
		if (isDestination( src, dest ))
		{
			return;
		}

		bool closedList[ROW][COL];
		std::memset( closedList, false, sizeof( closedList ) );

		std::vector<std::vector<cell>> cellDetails;

		int i, j;
		i = src.first, j = src.second;
		cellDetails[i][j].f = 0;
		cellDetails[i][j].g = 0;
		cellDetails[i][j].h = 0;
		cellDetails[i][j].parent = { i,j };

		std::priority_queue < Tuple, std::vector < Tuple>, std::greater<Tuple>> openList;

		openList.emplace( 0, i, j );

		while (!openList.empty())
		{
			const Tuple& p = openList.top();
			i = std::get<1>( p );
			j = std::get<2>( p );

			openList.pop();
			closedList[i][j] = true;

			for (int add_x = -1; add_x <= 1; add_x++)
			{
				for (int add_y = -1; add_y <= 1; add_y++)
				{
					Pair neighbour( i + add_x, j + add_y );
					if (isValide( grid, neighbour ))
					{
						if (isDestination( neighbour, dest ))
						{
							cellDetails[neighbour.first][neighbour.second].parent = { i,j };
							tracePath( cellDetails, dest );
							return;
						}
						else if (!closeList[neighbour.first][neighbour.second] && isUnBlocked( grid, neighbour ))
						{
							int gNew, hNew, fNew;
							gNew = cellDetails[i][j].g + 1.0;
							hNew = calculateHValue( neighbour, dest );
							fNew = gNew + hNew;
							if (cellDetails[neighbour.first][neighbour.second].f == -1 ||
								cellDetails[neighbour.first][neighbour.second].f > fNew)
							{
								openList.emplace( fNew, neighbour.first, neighbour.second );
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
	}
};

