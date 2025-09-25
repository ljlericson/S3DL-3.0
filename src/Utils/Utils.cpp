#include "Utils.h"

int Util::width = 1280,
	Util::height = 720;

static GLenum s_glErrCache = 0;

glm::ivec2 Util::viewportPos = glm::ivec2{ 0 };

// keep these private to this cpp file
// no init because static ints are
// init to 0 by default
static int s_widthBefore = 1280, 
		   s_heightBefore = 720;

void Util::updateWindowSize(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	if(width != s_widthBefore || height != s_heightBefore)
	{
		s_widthBefore = width;
		s_heightBefore = height;
		glViewport((GLint)viewportPos.x, (GLint)viewportPos.y, width, height);
	}
}

std::string Util::getFpathFromSelectionWindow()
{
	OPENFILENAME ofn;       // Common dialog box structure
	char szFile[260];       // Buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL; // Handle to the owner window (can be your main window handle)
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0"; // Filter for file types
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; // Initial directory
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return std::filesystem::relative(ofn.lpstrFile).string();
	}
	else
	{
		UTIL_ERR_LOG("No file selected\n");
		return "";
	}
}

bool Util::checkGlErrors()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		s_glErrCache = err;
		return true;
	}
	return false;
}

std::string Util::getGlErrAfterCheck()
{
	switch (s_glErrCache)
	{
	case GL_NO_ERROR:
		return "UTIL ERROR: No opengl error found |(or)| function called without check\n";
	case GL_INVALID_ENUM:
		return "OPENGL ERROR: Invalid enum\n";
	case GL_INVALID_VALUE:
		return "OPENGL ERROR: Invalid value\n";
	case GL_INVALID_OPERATION:
		return "OPENGL ERROR: Invalid opreation\n";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "OPENGL ERROR: Invalid framebuffer operation\n";
	case GL_OUT_OF_MEMORY:
		return "OPENGL ERROR: Out of memory\n";
	case GL_STACK_UNDERFLOW:
		return "OPENGL ERROR: Stack underflow\n";
	case GL_STACK_OVERFLOW:
		return "OPENGL ERROR: Stack overflow\n";
	default:
		return "UTIL ERROR: OpenGL error is not registered\n";
	}
}