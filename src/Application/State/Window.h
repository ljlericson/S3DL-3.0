#pragma once
#include <string>
#include <stdexcept>
#include <GLFW/glfw3.h>

namespace App
{
	namespace State
	{
		class Window
		{
		public:
			Window(const std::string& title, uint32_t w, uint32_t h);
			~Window();

			GLFWwindow* getWinHndle() const;

			bool getKeyDown(int32_t glfwKeyCode) const;

			bool getMouseClick(int32_t glfwKeyCode) const;

			void changeWindowName(const std::string& newName);

			void swapBuffers();

			void pollEvents();

		private:
			GLFWwindow* m_winHndle = nullptr;
		};
	}
}