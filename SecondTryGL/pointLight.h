#pragma once
#include "sphere.h"

class PointLight :
	public Sphere
{
public:
	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	PointLight(glm::vec3 location, float constant, float linear, float quadratic, 
		glm::vec3 ambient, glm::vec3 diffuse,
		glm::vec3 specular);
	~PointLight();
};

