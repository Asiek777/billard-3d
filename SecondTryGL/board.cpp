#include "board.h"



Board::Board(int width, int height)
{
	cubes.push_back(Cube(-width, -height - 1, -1.1f, -width - 1, height + 1, 0.2f, 0, 1, 0));
	cubes.push_back(Cube(-width, height, -1.1f, width, height + 1, 0.2f, 0, 1, 0));
	cubes.push_back(Cube(-width, -height, -1.1f, width, -height - 1, 0.2f, 0, 1, 0));
	cubes.push_back(Cube(width, -height - 1, -1.1f, width + 1, height + 1, 0.2f, 0, 1, 0));
	for (int i = -width; i < width; i++)
		for (int j = -height; j < height; j++)
			cubes.push_back(Cube(i, j, -1.1f, i + 1, j + 1, -1.0f, 0, 1, 0));

	cubeCount = cubes.size();
}

Board::~Board()
{
}
