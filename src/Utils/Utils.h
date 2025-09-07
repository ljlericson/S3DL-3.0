#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Util
{
	extern int width, height;

	void updateWindowSize(GLFWwindow* window);
}