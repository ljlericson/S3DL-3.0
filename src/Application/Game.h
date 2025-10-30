#pragma once
// std libraries
#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>
#include <array>
#include <thread>
#include <chrono>
#include <utility>
// nGL libraries
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// src files
#include "../Utils/Utils.h"
#include "../Utils/Timer.h"
#include "../Vender/ljlStat/src/include/ljl/Stat.hpp"

#include "../Core/Audio/Listener.h"
#include "../Core/Audio/Source.h"
#include "../Core/OpenGlBackend/Model.h"
#include "../Core/OpenGlBackend/camera.h"
//#include "../Core/OpenGlBackend/Fbo.h"
#include "../Core/OpenGlBackend/Shader.h"

#include "../Core/OpenGlBackend/CubeMap.h"

namespace Core::Manager
{
    class AssetManager;
}


namespace App 
{
    class Application
    {
    public:
		Application();
        void run();
        ~Application();

    private:
        enum class SampleType
        {
            control,
            test
        };

    private:
        void ImGuiPreRender();
        void ImGuiRender();
        void getImGuiStyle();
        void OpenGlPreRender();
        void OpenGlRender();
        void OpenGlPostRender();
        // fps sampling
        void sampleFps();

        GLFWwindow* m_window;
        ImFont* m_customFont;

        ljl::Stat::ContinuosSample m_fpsTestSamle;
        ljl::Stat::ContinuosSample m_fpsControlSamle;
        Util::Timer m_fpsSampleTimer;
        SampleType m_sampleType = SampleType::control;
        bool m_sampling = false;
        bool m_reTakeControl = false;

        Core::OpenGlBackend::Camera* m_camera = nullptr;
        Core::OpenGlBackend::CubeMap* m_skyBox = nullptr;
        //Core::OpenGlBackend::FBO* m_scrFBO = nullptr;
        Core::Manager::AssetManager* m_assetManager = nullptr;
        double m_statResult = -1.0;

        std::shared_ptr<Core::OpenGlBackend::Shader> m_shader;
        std::shared_ptr<Core::OpenGlBackend::Shader> m_shader2;
        std::shared_ptr<Core::OpenGlBackend::Shader> m_skyShad;

		std::vector<std::shared_ptr<Core::OpenGlBackend::Model>> m_models;

        Core::Audio::Listener* m_listener = nullptr;
        Core::Audio::Source* m_source = nullptr;

        glm::vec3 m_scrColor;
    };
}
