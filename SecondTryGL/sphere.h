#define _USE_MATH_DEFINES
#include <math.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>


class SphereSolid;

class Sphere {
private:
	glm::mat4 modelMat;
	static SphereSolid solid;
	void updateModelMat();

public:
	glm::vec3 color;
	glm::vec3 location;

	static std::vector<GLfloat> vertexData();
	static std::vector<GLushort> indices();
	glm::mat4 getModelMatrix() { return modelMat; }
	Sphere(glm::vec3 _color, glm::vec3 _location);
	Sphere(float Colorx, float Colory, float Colorz,
		float Locationx, float Locationy, float Locationz) : Sphere(
			glm::vec3(Colorx, Colory, Colorz),
			glm::vec3(Locationx, Locationy, Locationz)
		) {}
	void move(glm::vec3 direction, float deltaTime);
};




class SphereSolid
{
protected:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;


public:
	std::vector<GLushort> indices;
	std::vector<GLfloat> vertexData;
	int dataSize;


	SphereSolid(float radius, unsigned int rings, unsigned int sectors)
	{
		float const R = 1. / (float)(rings - 1);
		float const S = 1. / (float)(sectors - 1);
		int r, s;
		dataSize = rings * sectors;
		vertices.resize(dataSize * 3);
		normals.resize(dataSize * 3);
		texcoords.resize(dataSize * 2);
		std::vector<GLfloat>::iterator v = vertices.begin();
		std::vector<GLfloat>::iterator n = normals.begin();
		std::vector<GLfloat>::iterator t = texcoords.begin();
		for (r = 0; r < rings; r++) 
			for (s = 0; s < sectors; s++) {
				float const y = sin(-M_PI_2 + M_PI * r * R);
				float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
				float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

				*t++ = s * S;
				*t++ = r * R;

				*v++ = x * radius;
				*v++ = y * radius;
				*v++ = z * radius;

				*n++ = x;
				*n++ = y;
				*n++ = z;
			}

		indices.resize(dataSize * 6);
		std::vector<GLushort>::iterator i = indices.begin();
		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + s;
			*i++ = r * sectors + s;
		}
		vertexData.resize(dataSize * 6);
		for (int i = 0; i < dataSize; i++)
		{
			vertexData[6 * i + 0] = vertices[3 * i + 0];
			vertexData[6 * i + 1] = vertices[3 * i + 1];
			vertexData[6 * i + 2] = vertices[3 * i + 2];
			vertexData[6 * i + 3] = normals[3 * i + 0];
			vertexData[6 * i + 4] = normals[3 * i + 1];
			vertexData[6 * i + 5] = normals[3 * i + 2];
		}
	}
};