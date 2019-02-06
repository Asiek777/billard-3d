#include "cube.h"



std::vector<GLfloat> Cube::vertices = {
	0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f
};


std::vector<GLfloat> Cube::vertexData()
{
	return vertices;
}

Cube::Cube(glm::vec3 A, glm::vec3 B, glm::vec3 _color)
{
	color = _color;
	modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, A);
	modelMat = glm::scale(modelMat, B - A);

}



Cube::~Cube()
{
}
