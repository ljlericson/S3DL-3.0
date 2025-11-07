#include <string>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// windows specific (not usefull on mac)
 #include <windows.h>
 #include <commdlg.h> // For OPENFILENAME 

#include <glm/glm.hpp>

//#if defined(CORE_ENABLE_ERR_LOGS)
#if true
#define CORE_AUDIO_ERR_LOG(err) std::cout << "ERROR (Core::Audio): " << err << '\n'
#define CORE_GLIMPL_ERR_LOG(err) std::cout << "ERROR (Core::CORE_GLIMPL_ERR_LOG): " << err << '\n'
#else
#define CORE_AUDIO_ERR_LOG(err) 
#define CORE_GLIMPL_ERR_LOG(err) 
#endif

//#if defined(UTIL_ENABLE_ERR_LOGS)
#if true
#define UTIL_ERR_LOG(err) std::cout << "ERROR (UTIL): " << err << '\n'
#else
#define UTIL_ERR_LOG(err) 
#endif

namespace Util
{ 
	extern int width, height;
	extern glm::ivec2 viewportPos;

	void updateWindowSize(GLFWwindow* window);

	std::string getFpathFromSelectionWindow();
	void setWindowIconToICO();
	
	bool checkGlErrors();
	std::string getGlErrAfterCheck();

	void calcFps();

	double getFps();
}
