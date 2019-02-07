#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>


class Cube
{
private:
	glm::mat4 modelMat;
	static std::vector<float> vertices;
	
public:
	glm::vec3 color;

	static std::vector<GLfloat> vertexData();
	glm::mat4 getModelMatrix() { return modelMat; }

	Cube(glm::vec3 A, glm::vec3 B, glm::vec3 _color);

	Cube(float Ax, float Ay, float Az,
		float Bx, float By, float Bz,
		float Colorx, float Colory, float Colorz) : Cube(
			glm::vec3(Ax, Ay, Az),
			glm::vec3(Bx, By, Bz),
			glm::vec3(Colorx, Colory, Colorz)
		) {}
	
	~Cube();
};

