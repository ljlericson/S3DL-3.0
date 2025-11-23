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
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp> // For glm::rotate
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// ljl::Stat
#include <ljl/Stat.hpp>
// src files
#include "../Utils/Utils.h"
#include "../Utils/Timer.h"

#include "../Core/Audio/Listener.h"
#include "../Core/Audio/Source.h"
#include "../Core/OpenGlBackend/Model.h"
#include "../Core/OpenGlBackend/camera.h"
//#include "../Core/OpenGlBackend/Fbo.h"
#include "../Core/OpenGlBackend/Shader.h"

#include "../Core/OpenGlBackend/CubeMap.h"

#include "State/State.h"
#include "State/Window.h"

#include "Console/ChatStream.h"


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

        void inputs();
        // fps sampling
        void sampleFps();

        std::unique_ptr<State::Window> m_window;
        bool m_focus = false;
        bool m_firstMouseClick = true;
        bool m_sprinting = false;
        float m_speed = 2.5f;
        float m_mouseSens = 1.0f;
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
        std::unordered_map<std::string, std::vector<size_t>> m_modelInstaceIDs;

        Core::Audio::Listener* m_listener = nullptr;
        Core::Audio::Source* m_source = nullptr;

        glm::vec3 m_scrColor;
    };
}
