#include "sphere.h"


SphereSolid Sphere::solid = SphereSolid(1., 30, 30);

std::vector<GLfloat> Sphere::vertexData()
{
	return solid.vertexData;
}

std::vector<GLushort> Sphere::indices()
{
	return solid.indices;
}

Sphere::Sphere(glm::vec3 _color, glm::vec3 _location, float _radius)
{
	color = _color;
	location = _location;
	radius = _radius;
	updateModelMat();
}

void Sphere::updateModelMat()
{
	modelMat = glm::translate(glm::mat4(1.0), location);
	modelMat = glm::scale(modelMat, glm::vec3(radius));
}

void Sphere::move(glm::vec3 direction, float deltaTime) {
	location += deltaTime * direction * 3.0f;
	updateModelMat();
}
