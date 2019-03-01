#pragma once
#include "pointLight.h"
class Sun :
	public Sphere
{
	float alfa = 48.;
	const float orbit = 100;
	float lightStrength;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:	
	
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	glm::vec3 getSkyColor();
	glm::vec3 getFogColor();
	
	Sun(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~Sun();
	glm::vec3 getDirection();
	void move(float deltaFrame);
};

