#include "sun.h"



glm::vec3 Sun::getAmbient()
{
	return ambient * lightStrength;
}

glm::vec3 Sun::getDiffuse()
{
	return diffuse * lightStrength;
}

glm::vec3 Sun::getSpecular()
{
	return specular * lightStrength;
}

glm::vec4 Sun::getSkyColor()
{
	return glm::vec4(lightStrength*glm::vec3(0.3, 0.8, 1.), 1.0);
}

Sun::Sun(glm::vec3 _ambient, glm::vec3 _diffuse,
	glm::vec3 _specular) : Sphere(glm::vec3(1.), location, 8)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	move(0.);
}

Sun::~Sun()
{
}

glm::vec3 Sun::getDirection()
{

	return glm::normalize(-location);
}

void Sun::move(float deltaFrame)
{
	alfa += deltaFrame* 0.02;
	location = orbit * glm::vec3(
		cos(2) * sin(M_PI * alfa),
		sin(-M_PI_2 + M_PI * alfa),
		sin(2) * sin(M_PI * alfa)
	);
	lightStrength = location.z < 0 ? 0 : location.z / orbit;
	updateModelMat();
}
