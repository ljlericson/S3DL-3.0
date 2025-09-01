#pragma once
// std libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string_view>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <limits>
#include <cmath>
#include <chrono>
// opengl
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

// nGL libraries
#define GLAD_GL_IMPLEMENTATION
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
// audio
#include <AL/al.h>
#include <AL/alc.h>
// other stuff
#include <nlohmann/json.hpp>
//#include <assimp/Importer.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// windows specific
#include <windows.h>
#include <commdlg.h> // For OPENFILENAME structure
// src files
#include "../Utils/Timer.h"

namespace App 
{
    class Application
    {
    public:
		Application();
        void run();
        void shutdown();

    private:
        void ImGuiPreRender();
        void ImGuiRender();
        void getImGuiStyle();
        void OpenGlPreRender();
        void OpenGlRender();
        GLFWwindow* m_window;
        ImFont* m_customFont;
    };
}