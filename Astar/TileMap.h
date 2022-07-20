#pragma once
#include <array>
class TileMap
{
public:
	typedef enum{open, obstacle, close};
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
};

