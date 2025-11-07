#define CORE_ENABLE_ERR_LOGS
#include "Game.h"
#include "../Core/Manager/ModelManager.h"
#include "../Core/OpenGlBackend/Model.h"
#include "../Core/OpenGlBackend/camera.h"
//#include "../Core/OpenGlBackend/Fbo.h"
#include "../Core/OpenGlBackend/Shader.h"


 
void App::Application::getImGuiStyle()
 {
 	// Deep Dark style by janekb04 from ImThemes
 	ImGuiStyle& style = ImGui::GetStyle();
 
 	style.Alpha = 1.0f;
 	style.DisabledAlpha = 0.6000000238418579f;
 	style.WindowPadding = ImVec2(8.0f, 8.0f);
   	style.WindowRounding = 7.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(5.0f, 2.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
	style.CellPadding = ImVec2(6.0f, 6.0f);
	style.IndentSpacing = 25.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.9200000166893005f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.2899999916553497f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.239999994635582f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.3600000143051147f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 0.3300000131130219f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3600000143051147f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.3499999940395355f);
}

void App::Application::ImGuiPreRender()
{
	// ALL imgui rendering
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	int i = 0;
	bool show_demo_window = true;
	static int current_item = 0;
	const char* items[] = { "Option 1", "Option 2", "Option 3" };
	ImGui::Begin("Hello", &show_demo_window, ImGuiWindowFlags_MenuBar);
	ImGui::Text("ljl::Stat control sample avg: %f", m_fpsControlSamle.getMean());
	ImGui::Text("ljl::Stat Fps sampling result: %f", m_statResult);
	ImGui::Text("FPS: %f", Util::getFps());
	//getImGuiStyle();
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Print", "Ctrl+O")) { std::cout << "Hello World\n"; }
			if (ImGui::MenuItem("Open", "Ctrl+W"))
			{
				m_models.push_back(m_assetManager->getModelManager()->newModelOrGetModel(m_assetManager->getTextureManager(), Util::getFpathFromSelectionWindow()));
			}
			ImGui::EndMenu();
		}
		if (ImGui::Button("Recapture control sample"))
		{
			m_reTakeControl = true;
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::BeginCombo("Select option", items[current_item])) // Label + preview
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == n);
			if (ImGui::Selectable(items[n], is_selected))
				current_item = n;

			// Keep selection highlighted
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 6.0f));
	bool scrOpen = ImGui::CollapsingHeader("SCREEN");
	ImGui::PopStyleVar();
	if (scrOpen)
	{
		ImGui::ColorPicker3("Screen Color", glm::value_ptr(m_scrColor), ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
		ImGui::InputFloat("Noise Level Input", &m_camera->shaderNoiseLevel);
		ImGui::SliderFloat("Noise Level", &m_camera->shaderNoiseLevel, 0.0f, 10.0f);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 6.0f));
	bool movementOpen = ImGui::CollapsingHeader("MOVEMENT");
	ImGui::PopStyleVar();

	if (movementOpen)
	{
		ImGui::BeginChild("Movement Settings");
		ImGui::SliderFloat("Camera Speed", &m_camera->speed, 0.1f, 5.0f);
		ImGui::InputFloat("Camera Speed Input", &m_camera->speed);
		ImGui::SliderFloat("Camera Sens", &m_camera->sens, 0.1f, 3.0f);
		ImGui::Checkbox("Camera Grounded", &m_camera->grounded);
		if(ImGui::Button("Reset Camera"))
		{
			m_camera->pos = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		ImGui::EndChild();
	} 

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 6.0f));
	bool modelOpen = ImGui::CollapsingHeader("MODELS");
	ImGui::PopStyleVar();
	if (modelOpen)
	{

		ImGui::BeginChild("Model Settings");
		for (auto& model : m_models)
		{
			ImGui::PushID((int)model->getLocalID());
			if (ImGui::CollapsingHeader(model->m_name.c_str()))
			{
				if (ImGui::CollapsingHeader(((model->m_name.c_str()) + std::string(" INFO")).c_str()))
				{
					ImGui::Text("Number of textures: %d", model->getNumTextures());
					ImGui::Text("Loacl ID: %d", model->getLocalID());
				}
				if (ImGui::CollapsingHeader(((model->m_name.c_str()) + std::string(" MOVE")).c_str()))
				{
					ImGui::InputFloat3((model->m_name.c_str() + std::string(" Pos Input")).c_str(), glm::value_ptr(model->m_pos));
					ImGui::SliderFloat3((model->m_name.c_str() + std::string(" Pos Slider")).c_str(), glm::value_ptr(model->m_pos), -100.0f, 100.0f);
					if (ImGui::Button("Paste on camera"))
					{
						model->m_pos = m_camera->pos;
					}
				}
				if(ImGui::Button((std::string("Delete ") + model->m_name.c_str()).c_str()))
				{
					m_models.erase(std::remove(m_models.begin(), m_models.end(), model), m_models.end());
					ImGui::PopID();
					break; // Exit the loop to avoid invalid iterator access
				}
			}
			ImGui::PopID();
		}
		if (ImGui::Button("New Model"))
		{
			m_models.push_back(
				m_assetManager->getModelManager()->newModelOrGetModel(
					m_assetManager->getTextureManager(), 
					Util::getFpathFromSelectionWindow()
				));
		}
		ImGui::EndChild();
	}

	if (ImGui::Button("Load new sound"))
	{
		if (m_source)
			delete m_source;

		m_source = new Core::Audio::Source(m_assetManager, Util::getFpathFromSelectionWindow().c_str(), glm::vec3(0.0f));
	}
	
	// end of window
	//ImGui::PopFont();
	ImGui::End();
}

void App::Application::ImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::Application::sampleFps()
{
	constexpr float controlDurationMs = 5000.0f;
	constexpr float testDelayMs = 3000.0f; // wait after control ends
	constexpr float testDurationMs = 3000.0f;
	constexpr float sampleIntervalMs = 100.0f;

	static float lastSampleTime = 0.0f;

	switch (m_sampleType)
	{
	case SampleType::control:
		if (!m_sampling) 
		{
			std::cout << "\n--- CAPTURING CONTROL SAMPLE ---\n";
			m_fpsSampleTimer.reset();
			lastSampleTime = 0.0f;
			m_sampling = true;
		}
		else 
		{
			float t = m_fpsSampleTimer.sinceStarted();
			if (t - lastSampleTime >= sampleIntervalMs) 
			{
				m_fpsControlSamle << Util::getFps();
				lastSampleTime = t;
			}

			if (t >= controlDurationMs) 
			{
				m_sampling = false;
				m_sampleType = SampleType::test;
				m_fpsSampleTimer.reset();
				std::cout <<   "=== CONTROL SAMPLE COMPLETE  ===\n"
					<< "MEAN: " << m_fpsControlSamle.getMean() << '\n'
					<< "VAR : " << m_fpsControlSamle.getVar() << '\n';
			}
		}
		break;

	case SampleType::test:
		if (m_reTakeControl)
		{
			m_sampling = false;
			m_reTakeControl = false;
			m_fpsTestSamle = {};
			m_fpsControlSamle = {};
			m_sampleType = SampleType::control;
			break;
		}
		float t = m_fpsSampleTimer.sinceStarted();

		if (!m_sampling && t >= testDelayMs) 
		{
			m_fpsSampleTimer.reset();
			lastSampleTime = 0.0f;
			m_sampling = true;
		}
		else if (m_sampling) 
		{
			float t2 = m_fpsSampleTimer.sinceStarted();
			if (t2 - lastSampleTime >= sampleIntervalMs) 
			{
				m_fpsTestSamle << Util::getFps();
				lastSampleTime = t2;
			}

			if (t2 >= testDurationMs) 
			{
				m_sampling = false;
				m_statResult = ljl::Stat::HY_getCriticalSignificanLevel<ljl::Stat::ContinuosSample>(
					ljl::Stat::HypothTestType::hasChanged,
					ljl::Stat::PopVarianceEstimationType::usePopulation,
					m_fpsControlSamle,
					m_fpsTestSamle);

				m_fpsTestSamle = {};
			}
		}
		break;
	}
}

void App::Application::OpenGlPreRender()
{
	Util::updateWindowSize(m_window);
	//m_scrFBO->startPreRender();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_scrColor.x, m_scrColor.y, m_scrColor.z, 1.0f);
}

void App::Application::OpenGlRender()
{
	m_skyBox->draw(m_skyShad.get(), m_camera);

	for (auto& model : m_models)
	{
		//if ((model->getLocalID() % 2) == 0)
			//model->Draw(m_shader2.get(), m_camera);
		//else
			model->Draw(m_shader.get(), m_camera);
	}
}

void App::Application::OpenGlPostRender()
{
	//m_scrFBO->postRender();
}

App::Application::Application()
	: m_scrColor{ 169.0f / 255.0f, 222.0f / 255.0f, 250.0f / 255.0f }
{
#ifdef __APPLE__
	std::filesystem::path newDir = "/Users/linus/Desktop/S3DL-3.0/";
	std::filesystem::current_path(newDir);
#endif

	if (glfwInit() != GLFW_TRUE)
	{
		const char* description;
		int code = glfwGetError(&description);

		std::cerr << "GLFW initialization failed, error code: " << code << "\n";
		if (description)
			std::cerr << "Error description: " << description << "\n";
		else
			std::cerr << "No error description available.\n";
	}
	// provide glfw with relevent info
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// wanting to keep initialsation code explicit
	m_window = glfwCreateWindow(1280, 720, "s3gl 3.0", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if (glfwGetCurrentContext() != m_window) 
	{
		std::cerr << "OpenGL context is not current before ImGui device object creation.\n";
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLEW failed to init, error: " << glGetError() << '\n';
	}

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);       // Enable face culling
	glCullFace(GL_BACK);          // Don't draw back faces
	glFrontFace(GL_CCW);          // Default winding is counter-clockwise
	glViewport(0, 0, 1280, 720);
	glfwSwapInterval(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	stbi_set_flip_vertically_on_load(true);


	// imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	if (!ImGui_ImplOpenGL3_Init("#version 410")) 
	{
		std::cerr << "ImGui OpenGL3 backend failed to initialize.\n";
		throw std::runtime_error("ImGui OpenGL3 backend failed to initialize.");
	}
	//m_customFont = io.Fonts->AddFontFromFileTTF("assets/fonts/western.ttf", 16.0f);

	Util::setWindowIconToICO();

	m_assetManager = new Core::Manager::AssetManager{};

	m_camera = new Core::OpenGlBackend::Camera(glm::vec3(0.0f, 0.0f, 0.0f));
	m_camera->fov = 90.0f;
	m_camera->update_matrix(0.1f, 10000.0f);

	m_skyBox = new Core::OpenGlBackend::CubeMap(
		"assets/skybox/px.png",
		"assets/skybox/nx.png",
		"assets/skybox/py.png",
		"assets/skybox/ny.png",
		"assets/skybox/pz.png",
		"assets/skybox/nz.png"
		/*"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
		"assets/skybox/front.jpg",
		"assets/skybox/back.jpg"*/
	);

	m_shader = m_assetManager->getShadManager()->newShaderOrGetShader<Core::OpenGlBackend::Shader>("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
	m_shader2 = m_assetManager->getShadManager()->newShaderOrGetShader<Core::OpenGlBackend::Shader>("assets/shaders/vert2.glsl", "assets/shaders/frag2.glsl");
	m_skyShad = m_assetManager->getShadManager()->newShaderOrGetShader<Core::OpenGlBackend::Shader>("assets/shaders/skyBoxVert.glsl", "assets/shaders/skyBoxFrag.glsl");
    
    m_listener = new Core::Audio::Listener(glm::vec3(0.0f));

	//m_scrFBO = new Render::FBO{ "assets/shaders/frameBufferVert.glsl", "assets/shaders/frameBufferFrag.glsl" };
	//if (!m_scrFBO)
	//	throw;
}

void App::Application::run()
{
	 m_assetManager->getShadManager()->doHotReloads(true, Core::Manager::ShaderManager::HotLoading::runOnDifferentThread);

    while(!glfwWindowShouldClose(m_window))
    {
		m_camera->update_matrix(0.1f, 1000000.0f);
		m_camera->inputs(m_window, 0);

		m_listener->orientation = m_camera->getOrientation();
		m_listener->pos = m_camera->pos;
		m_listener->update();
		if (m_source)
		{
			m_source->play(1);
		}
		
		// shader hot loading
		if (m_assetManager->getShadManager()->hotReloadLoop<Core::OpenGlBackend::Shader>())
		{
			if (m_shader->getID() == 0)
				m_shader = m_assetManager->getShadManager()->getShader<Core::OpenGlBackend::Shader>("assets/shaders/vert.glsl");

			if (m_shader2->getID() == 0)
				m_shader2 = m_assetManager->getShadManager()->getShader<Core::OpenGlBackend::Shader>("assets/shaders/vert2.glsl");

			if (m_skyShad->getID() == 0)
				m_skyShad = m_assetManager->getShadManager()->getShader<Core::OpenGlBackend::Shader>("assets/shaders/skyBoxVert.glsl");
		}

		m_assetManager->getModelManager()->loop();

		Util::calcFps();

		sampleFps();

		OpenGlPreRender();

		OpenGlRender();

		OpenGlPostRender();

		ImGuiPreRender();

		ImGuiRender();
        // swap buffers 
        glfwSwapBuffers(m_window);
        // poll events
        glfwPollEvents();
    }

	 m_assetManager->getShadManager()->doHotReloads(false, Core::Manager::ShaderManager::HotLoading::runOnDifferentThread);
}

App::Application::~Application()
{
	if(m_camera)
		delete m_camera;
	/*if (m_scrFBO)
		delete m_scrFBO;*/

	glfwTerminate();
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();

	std::cout << "All good things must come to an end" << /* finally flush the stream */ std::endl;
}
