#pragma once
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


namespace Util
{ 
	extern int width, height;
	extern glm::vec2 viewportPos;

	void updateWindowSize(GLFWwindow* window);
	
	bool checkGlErrors();
	std::string getGlErrAfterCheck();
}