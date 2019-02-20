#include "pointLight.h"




PointLight::PointLight(glm::vec3 location, float _constant, float _linear, float _quadratic,
	glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) : Sphere(glm::vec3(1.), location)
{
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}

PointLight::~PointLight()
{
}
