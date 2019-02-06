#include "sphere.h"


SphereSolid Sphere::solid = SphereSolid(1., 20, 20);

std::vector<GLfloat> Sphere::vertexData()
{
	return solid.vertexData;
}

std::vector<GLushort> Sphere::indices()
{
	return solid.indices;
}

Sphere::Sphere(glm::vec3 _color, glm::vec3 _location)
{
	color = _color;
	location = _location;
	updateModelMat();
}

void Sphere::updateModelMat()
{
	modelMat = glm::translate(glm::mat4(1.0), location);
}

void Sphere::moveUp() {
	location.y+=0.01;
	updateModelMat();
}
