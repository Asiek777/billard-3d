#pragma once
#include "sun.h"
#include "cube.h"
class Lamp
{
	float alfa = 45;
	float yawn = 0;
	glm::mat4 lampModelMat;
	glm::mat4 rotateMatrix;

	void updateModelMatrix();

public:
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	Cube block;
	Cube stick;
	Sphere light;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Lamp(float constant, float linear, float quadratic,
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float cutOff, float outerCutOff);
	~Lamp();
	void move(float deltaFrame);
	void rotate(float deltaFrame);
	glm::mat4 getModelMatrix(bool isRotated = false);
	glm::vec3 getLightLocation();
	glm::vec3 getLightDirection();
};

