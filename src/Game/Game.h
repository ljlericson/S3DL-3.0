#pragma once
// std libraries
#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>
#include <array>
// nGL libraries
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// windows specific
#include <windows.h>
#include <commdlg.h> // For OPENFILENAME structure
// src files
#include "../Utils/Utils.h"
#include "../Utils/Timer.h"
#include "../Core/OpenGlBackend/Model.h"
#include "../Core/OpenGlBackend/camera.h"
#include "../Core/OpenGlBackend/Fbo.h"
#include "../Core/Audio/Listener.h"
#include "../Core/Audio/Source.h"



namespace App 
{
    class Application
    {
    public:
		Application();
        void run();
        ~Application();

    private:
        void ImGuiPreRender();
        void ImGuiRender();
        void getImGuiStyle();
        void OpenGlPreRender();
        void OpenGlRender();
        void OpenGlPostRender();
        GLFWwindow* m_window;
        ImFont* m_customFont;

        Core::OpenGlBackend::Camera* m_camera = nullptr;
        Core::OpenGlBackend::Shader* m_shader = nullptr;
        Core::OpenGlBackend::FBO* m_scrFBO = nullptr;
		std::vector<std::unique_ptr<Core::OpenGlBackend::Model>> m_models;

        glm::vec3 m_scrColor;
        bool m_getNewFile = false;
        std::string m_selectedFile;
    };
}