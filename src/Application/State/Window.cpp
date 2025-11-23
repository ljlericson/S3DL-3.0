#include "Window.h"

namespace App
{
	namespace State
	{
		Window::Window(const std::string& title, uint32_t w, uint32_t h)
		{
			m_winHndle = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);

			if (m_winHndle == NULL)
			{
				glfwTerminate();
				throw std::runtime_error("\n======== WINDOW FAILED DURING CONSTRUCTION (1) ========\n");
			}

			glfwMakeContextCurrent(m_winHndle);

			if (glfwGetCurrentContext() != m_winHndle)
			{
				glfwTerminate();
				throw std::runtime_error("\n======== WINDOW FAILED DURING CONSTRUCTION (2) ========\n");
			}
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_winHndle);
		}

		GLFWwindow* Window::getWinHndle() const
		{
			return m_winHndle;
		}

		bool Window::getKeyDown(int32_t glfwKeyCode) const
		{
			return (glfwGetKey(m_winHndle, glfwKeyCode) == GLFW_KEY_DOWN);
		}

		bool Window::getMouseClick(int32_t glfwKeyCode) const
		{
			return (glfwGetMouseButton(m_winHndle, glfwKeyCode) == GLFW_PRESS);
		}

		void Window::changeWindowName(const std::string& newName)
		{
			
		}

		void Window::swapBuffers()
		{
			glfwSwapBuffers(m_winHndle);
		}

		void Window::pollEvents()
		{
			glfwPollEvents();
		}
	}
}