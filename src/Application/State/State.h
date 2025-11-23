#pragma once
#include <iostream>
#include <string>
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace App
{
	namespace State
	{
		void initGLFW();

		void initGL();

		void terminate();
	}
}