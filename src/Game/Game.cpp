#include "Game.h"

void App::Application::start()
{
    m_window = glfwCreateWindow(1280, 720, "s3gl 3.0", NULL, NULL);
    glfwMakeContextCurrent(m_window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // white burns my eyes
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void App::Application::run()
{
    while(!glfwWindowShouldClose(m_window))
    {

    }
}

void App::Application::shutdown()
{

}