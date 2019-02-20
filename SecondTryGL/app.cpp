#define STB_IMAGE_IMPLEMENTATION
#include "app.h"


App* App::instance = nullptr;

App::App()
{
	camera = &followCamera;
	cameras = new Camera*[4] {
		&freeCamera, &constCamera, &toBallCamera, &followCamera
	};
	instance = this;
}

App::~App()
{
	delete cameras;
}

int App::run() {
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callbackGlobal);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callbackGlobal);
	glfwSetScrollCallback(window, scroll_callbackGlobal);

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
	
	unsigned int ballVBO, cubeVBO, ballVAO, cubeVAO, EBO;
	SetupBuffers(ballVAO, cubeVAO, ballVBO, cubeVBO, EBO);

	Shader phongShader("phong.vert", "phong.frag");
	phongShaderPtr = &phongShader;
	mainShader = &phongShader;
	mainShader->use();

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		mainShader->use();

		setUniforms();

		glBindVertexArray(ballVAO);
		for (unsigned int i = 0; i < 9; i++)
			renderBall(*mainShader, spheres[i]);
		renderBall(*mainShader, whiteBall);

		glBindVertexArray(cubeVAO);
		for (int i = 0; i < table.cubeCount; i++)
			renderCube(*mainShader, table[i]);


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

void App::SetupBuffers(unsigned int &ballVAO, unsigned int &cubeVAO, unsigned int &ballVBO, unsigned int &cubeVBO, unsigned int &EBO)
{
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
}

void App::setUniforms()
{
	glm::mat4 view = camera->GetViewMatrix();
	mainShader->setMat4("view", view);
	glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (float)screenWidth / screenHeight, 0.1f, 100.0f);
	mainShader->setMat4("projection", projection);
	mainShader->setVec3("viewPos", camera->getPosition());
	mainShader->setFloat("shininess", 64);

	mainShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	mainShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	mainShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	mainShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


	mainShader->setVec3("pointLights.position", 4.0f, -3.0f, 4.0f);
	mainShader->setVec3("pointLights.ambient", 0.05f, 0.05f, 0.05f);
	mainShader->setVec3("pointLights.diffuse", 0.8f, 0.8f, 0.8f);
	mainShader->setVec3("pointLights.specular", 1.0f, 1.0f, 1.0f);
	mainShader->setFloat("pointLights.constant", 1.0f);
	mainShader->setFloat("pointLights.linear", 0.09);
	mainShader->setFloat("pointLights.quadratic", 0.032);


	mainShader->setVec3("spotLight.position", freeCamera.getPosition());
	mainShader->setVec3("spotLight.direction", freeCamera.Front);
	mainShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	mainShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	mainShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	mainShader->setFloat("spotLight.constant", 1.0f);
	mainShader->setFloat("spotLight.linear", 0.09);
	mainShader->setFloat("spotLight.quadratic", 0.032);
	mainShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	mainShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

App * App::getInstance()
{
	return instance;
}

void App::renderCube(Shader & shader, Cube& cube)
{
	shader.setVec3("objectColor", cube.color);
	shader.setMat4("model", cube.getModelMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void App::renderBall(Shader &shader, Sphere &ball)
{
	shader.setVec3("objectColor", ball.color);
	shader.setMat4("model", ball.getModelMatrix());
	glDrawElements(GL_TRIANGLES, Sphere::indices().size(), GL_UNSIGNED_SHORT, 0);
}

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, screenWidth, screenHeight);
}

void App::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void App::processInput(GLFWwindow *window) {
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

void App::changeCamera() {
	static int i = 0;
	i = (i + 1) % 4;
	camera = cameras[i];
}


