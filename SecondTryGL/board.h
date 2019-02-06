#pragma once
#include "cube.h"

class Board
{
private:
	Cube *cubes;

public:
	int cubeCount;
	Cube operator[](int i) { return cubes[i]; }

	Board(int width, int height);
	~Board();
};

