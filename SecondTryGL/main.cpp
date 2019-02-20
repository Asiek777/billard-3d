#include "app.h"


//void framebuffer_size_callbackGlobal(GLFWwindow* window, int width, int height);
//void mouse_callbackGlobal(GLFWwindow* window, double xpos, double ypos);
//void scroll_callbackGlobal(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	App app;
	return app.run();
}


void framebuffer_size_callbackGlobal(GLFWwindow * window, int width, int height)
{
	App::getInstance()->framebuffer_size_callback(window, width, height);
}

void mouse_callbackGlobal(GLFWwindow * window, double xpos, double ypos)
{
	App::getInstance()->mouse_callback(window, xpos, ypos);
}

void scroll_callbackGlobal(GLFWwindow * window, double xoffset, double yoffset)
{
	App::getInstance()->scroll_callback(window, xoffset, yoffset);
}