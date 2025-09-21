#include "Utils.h"

int Util::width = 1280,
	Util::height = 720;

static GLenum s_glErrCache = 0;

glm::vec2 Util::viewportPos = glm::vec2{ 0.0f };

// keep these private to this cpp file
// no init because static ints are
// init to 0 by default
static int s_widthBefore = 1280, 
		   s_heightBefore = 720;

void Util::updateWindowSize(GLFWwindow* window)
{
	int mwidth = width, mheight = height;

	glfwGetFramebufferSize(window, &mwidth, &mheight);
	if(width != s_widthBefore || height != s_heightBefore)
	{
		s_widthBefore = width;
		s_heightBefore = height;
		// cast to allow for ImGui view port pos being stored as float
		glViewport((GLint)viewportPos.x, (GLint)viewportPos.y, width, height);
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
		return "UTIL ERROR: No opengl error found\n";
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