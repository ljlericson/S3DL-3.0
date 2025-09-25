#pragma once
#include <print>
#include <string>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// windows specific
#include <windows.h>
#include <commdlg.h> // For OPENFILENAME structure

#include <glm/glm.hpp>

//#if defined(CORE_ENABLE_ERR_LOGS)
#if true
#define CORE_AUDIO_ERR_LOG(err) std::print("ERROR (Core::Audio): {}\n", err)
#define CORE_GLIMPL_ERR_LOG(err) std::print("ERROR (Core::OpenGlBackend): {}\n", err)
#else
#define CORE_AUDIO_ERR_LOG(err) 
#define CORE_GLIMPL_ERR_LOG(err) 
#endif

//#if defined(UTIL_ENABLE_ERR_LOGS)
#if true
#define UTIL_ERR_LOG(err) std::print("ERROR (Util): {}\n", err)
#else
#define UTIL_ERR_LOG(err) 
#endif

namespace Util
{ 
	extern int width, height;
	extern glm::ivec2 viewportPos;

	void updateWindowSize(GLFWwindow* window);

	std::string getFpathFromSelectionWindow();
	
	bool checkGlErrors();
	std::string getGlErrAfterCheck();
}