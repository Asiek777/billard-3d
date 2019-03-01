#pragma once
#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GLFW/glfw3.h>


#include "stb_image.h"

#include <iostream>
#include <fstream>

#include "shader_s.h"
#include "camera.h"
//#include "sphere.h"
#include "cube.h"
#include "board.h"
//#include "pointLight.h"
#include "sun.h"
#include "lamp.h"

void framebuffer_size_callbackGlobal(GLFWwindow* window, int width, int height);
void mouse_callbackGlobal(GLFWwindow* window, double xpos, double ypos);
void scroll_callbackGlobal(GLFWwindow* window, double xoffset, double yoffset);

class App {

	int screenWidth = 800, screenHeight = 600;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float lastX = screenWidth / 2.f, lastY = screenHeight / 2.f;
	bool firstMouse = true;

	Board table = Board(30, 20);
	Sphere whiteBall = Sphere(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.0f));
	PointLight lightBall = PointLight(glm::vec3(15., 10., 4), 1., 0.09, 0.032,
		glm::vec3(0.25), glm::vec3(0.6), glm::vec3(1.));
	Sun sun = Sun(glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));
	Lamp lamp = Lamp(1., 0.09, 0.032,
		glm::vec3(0.), glm::vec3(1.), glm::vec3(1.),
		glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
	bool isFog = true;

	FreeCamera freeCamera = FreeCamera(glm::vec3(0.f, 0.f, 55.f));
	ConstCamera constCamera = ConstCamera();
	ToBallCamera toBallCamera = ToBallCamera(glm::vec3(0.f, 0.f, 0.f));
	FollowCamera followCamera = FollowCamera(glm::vec3(0.f, 0.f, 0.f));
	Camera *camera;
	Camera **cameras;

	Shader* phongShaderPtr;
	Shader* gourandShaderPtr;
	Shader* mainShader;
	Shader* lightShaderPtr;

	static App* instance;


	void renderBall(Shader &, Sphere &, unsigned int & vertexArray);
	void renderCube(Shader &, Cube&, unsigned int & vertexArray);
	void renderLamp(Shader& main, Shader& light, Lamp& lamp, unsigned int& ballVAO, unsigned int& cubeVAO);
	void processInput(GLFWwindow *window);
	void changeCamera();
	void SetupBuffers(unsigned int &ballVAO, unsigned int &cubeVAO, unsigned int &ballVBO, unsigned int &cubeVBO, unsigned int &EBO);
	void setUniforms();

public:
	App();
	~App();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	int run();

	static App* getInstance();
};

