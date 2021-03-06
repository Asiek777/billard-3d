#pragma once
#include "cube.h"

class Board
{
private:
	std::vector<Cube> cubes;

public:
	int cubeCount;
	Cube operator[](int i) const { return cubes[i]; }
	Cube& operator[](int i) { return cubes[i]; }

	Board(int width, int height);
	~Board();
};

