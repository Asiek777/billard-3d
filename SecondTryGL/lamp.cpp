#include "lamp.h"



Lamp::Lamp(float _constant, float _linear, float _quadratic,
	glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, 
	float _cutOff, float _outerCutOff) : 
	light(0,0,0, 0, 0, -0.25, 0.25),
	block(-0.3, -0.3, -0.42, 0.3, 0.3, 0.1, 0.1, 0.1, 0.1),
	stick(-0.1, -0.1, -0.3, 0.1, 0.1, 2, 0.1, 0.1, 0.1)
{
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	cutOff = _cutOff;
	outerCutOff = _outerCutOff;
	rotateMatrix = glm::mat4(1.0);
	updateModelMatrix();
}

Lamp::~Lamp()
{
}

void Lamp::move(float deltaFrame)
{
	alfa += deltaFrame * 0.07;
	updateModelMatrix();
}

void Lamp::rotate(float deltaFrame)
{
	yawn += deltaFrame * 0.2;
	rotateMatrix = glm::rotate(glm::mat4(1.0), yawn, glm::vec3(1, 0, 0));
}

void Lamp::updateModelMatrix()
{
	lampModelMat = glm::mat4(1.0);
	lampModelMat = glm::rotate(lampModelMat, alfa, glm::vec3(0, 0, 1));
	lampModelMat = glm::translate(lampModelMat, glm::vec3(0, 2, 3));
	lampModelMat = glm::rotate(lampModelMat, 0.22f * (float)M_PI, glm::vec3(1, 0, 0));

}

glm::mat4 Lamp::getModelMatrix(bool isRotated)
{
	if (isRotated)
		return lampModelMat * rotateMatrix;
	else
		return lampModelMat;
}

glm::vec3 Lamp::getLightLocation()
{
	return glm::vec3(getModelMatrix(true) * glm::vec4(light.location, 1.0));
}

glm::vec3 Lamp::getLightDirection()
{
	return glm::vec3(getModelMatrix(true) * glm::vec4(0, 0, -1, 0));
}
