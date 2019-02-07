#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <fstream>

#include "shader_s.h"
#include "camera.h"
#include "sphere.h"
#include "cube.h"
#include "board.h"



int screenWidth = 800, screenHeight = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = screenWidth / 2.f, lastY = screenHeight / 2.f;
bool firstMouse = true;
Sphere whiteBall(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

FreeCamera freeCamera(glm::vec3(0.f, 0.f, 55.f));
ConstCamera constCamera = ConstCamera();
ToBallCamera toBallCamera(glm::vec3(0.f, 0.f, 0.f));
FollowCamera followCamera(glm::vec3(0.f, 0.f, 0.f));
Camera *camera = &followCamera;
Camera *cameras[] = { &freeCamera, &constCamera, &toBallCamera, &followCamera };


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void renderBall(Shader &ballShader, Sphere &ball);
void renderCube(Shader & shader, Cube& cube);
void processInput(GLFWwindow *window);
void changeCamera();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);




int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glEnable(GL_DEPTH_TEST);
	
	Sphere spheres[] = {
		Sphere(glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec3(2.0f,  5.0f, 0.0f)),
		Sphere(glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec3(-1.5f, -2.2f, 0.0f)),
		Sphere(glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(-3.8f, -2.0f, 0.0f)),
		Sphere(glm::vec3(0.2f, 0.0f, 1.0f),	glm::vec3(3.4f, -5.4f, 0.0f)),
		Sphere(glm::vec3(0.0f, 0.4f, 0.5f),	glm::vec3(-1.7f,  3.0f, 0.0f)),
		Sphere(glm::vec3(0.1f, 0.4f, 0.0f),	glm::vec3(1.3f, -2.0f, 0.0f)),
		Sphere(glm::vec3(1.0f, 0.4f, 0.0f),	glm::vec3(1.5f,  2.0f, 0.0f)),
		Sphere(glm::vec3(1.0f, 0.4f, 0.6f),	glm::vec3(1.5f,  0.2f, 0.0f)),
		Sphere(glm::vec3(0.0f, 0.9f, 0.1f),	glm::vec3(-1.3f,  1.0f, 0.0f))
	};

	Board table(30, 20);
	//Cube cubes = Cube(glm::vec3(-1.0, -1.0, -1.0), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(1.0f, 0.4f, 0.6f));

	
	unsigned int ballVBO, cubeVBO , ballVAO, cubeVAO, EBO;
	glGenVertexArrays(1, &ballVAO);
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &ballVBO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &EBO);

	
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, Cube::vertexData().size() * sizeof(GLfloat), Cube::vertexData().data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(ballVAO);
	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
	glBufferData(GL_ARRAY_BUFFER, Sphere::vertexData().size() * sizeof(GLfloat), Sphere::vertexData().data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sphere::indices().size() * sizeof(GLfloat), Sphere::indices().data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	Shader ballShader("ball.vert", "ball.frag");

	ballShader.use();
	ballShader.setVec3("lightPos", glm::vec3(4.0f, -3.0f, 4.0f));
	glm::mat4 projection;


	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ballShader.use();

		glm::mat4 view = camera->GetViewMatrix();
		ballShader.setMat4("view", view);

		projection = glm::perspective(glm::radians(camera->getZoom()), (float)screenWidth / screenHeight, 0.1f, 100.0f);
		ballShader.setMat4("projection", projection);
		ballShader.setVec3("viewPos", camera->getPosition());

		glBindVertexArray(ballVAO);
		for (unsigned int i = 0; i < 9; i++)
			renderBall(ballShader, spheres[i]);
		renderBall(ballShader, whiteBall);

		glBindVertexArray(cubeVAO);
		for (int i = 0; i < table.cubeCount; i++)
			renderCube(ballShader, table[i]);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &ballVAO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &ballVBO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &EBO);

	//system("pause");
	glfwTerminate();
	return 0;
}

void renderCube(Shader & shader, Cube& cube)
{
	shader.setVec3("ballColor", cube.color);
	shader.setMat4("model", cube.getModelMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderBall(Shader &shader, Sphere &ball)
{
	shader.setVec3("ballColor", ball.color);
	shader.setMat4("model", ball.getModelMatrix());
	glDrawElements(GL_TRIANGLES, Sphere::indices().size(), GL_UNSIGNED_SHORT, 0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, screenWidth, screenHeight);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) 
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	freeCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		freeCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		freeCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		freeCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		freeCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		whiteBall.move(followCamera.getDirection(), deltaTime);
		toBallCamera.updateBallPosition(whiteBall.location);
		followCamera.updateBallPosition(whiteBall.location);

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		whiteBall.move(followCamera.getDirection(), -deltaTime);
		toBallCamera.updateBallPosition(whiteBall.location);
		followCamera.updateBallPosition(whiteBall.location);

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)	
		followCamera.updateDirection(-deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		followCamera.updateDirection(deltaTime);

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		changeCamera();
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		camera = cameras[0];
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		camera = cameras[1];
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		camera = cameras[2];
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		camera = cameras[3];
}

void changeCamera() {
	static int i = 0;
	i = (i + 1) % 4;
	camera = cameras[i];
}