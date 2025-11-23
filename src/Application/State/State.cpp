#include "State.h"

namespace App
{
	namespace State
	{
		void initGLFW()
		{
			if (glfwInit() != GLFW_TRUE)
			{
				const char* description;
				int code = glfwGetError(&description);

				std::cerr << "GLFW initialization failed, error code: " << code << "\n";
				if (description)
					std::cerr << "Error description: " << description << "\n";
				else
					std::cerr << "No error description available.\n";
			}
			// provide glfw with relevent info
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void initGL()
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "glad failed to initialize OpenGL function pointers.\n";

				const char* desc = nullptr;
				int code = glfwGetError(&desc);
				std::cerr << "GLFW error code: " << code;
				if (desc) std::cerr << ", desc: " << desc;
				std::cerr << "\n";
				throw std::runtime_error("Failed to initialize OpenGL loader.");
			}

			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);       // Enable face culling
			glCullFace(GL_BACK);          // Don't draw back faces
			glFrontFace(GL_CCW);          // Default winding is counter-clockwise
			glViewport(0, 0, 1280, 720);
			glfwSwapInterval(0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void terminate()
		{
			glfwTerminate();
		}
	}
}