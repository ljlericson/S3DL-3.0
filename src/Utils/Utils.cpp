#include "Utils.h"

int Util::width = 1280;
int Util::height = 720;

void Util::updateWindowSize(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}