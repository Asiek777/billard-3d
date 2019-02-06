#include "board.h"



Board::Board(int width, int height)
{
	cubeCount = 5;
	cubes = new Cube[cubeCount]{
		Cube(-width, -height, -1.1f, width, height, -1.0f, 0, 1, 0),
		Cube(-width, height, -1.1f, width, height + 1, 0.2f, 0, 1, 0),
		Cube(-width, -height, -1.1f, width, -height - 1, 0.2f, 0, 1, 0),
		Cube(width, -height - 1, -1.1f, width + 1, height + 1, 0.2f, 0, 1, 0),
		Cube(-width, -height - 1, -1.1f, -width - 1, height + 1, 0.2f, 0, 1, 0)
	};
}

Board::~Board()
{
	delete[] cubes;
}
