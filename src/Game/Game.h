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
#include <GL/glew.h>
#include <glfw/glfw3.h>
// gl maths library
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
// OpenAl
#include <AL/al.h>
#include <AL/alc.h>
// the holy grail?
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// stb
#include <stb/stb_image.h>
// json parsing
#include <nlohmann/json.hpp>
// src files
#include "../Utils/Timer.h"
#include "../Utils/Timer.h"
#include "../Utils/Timer.h"

namespace App 
{
    class Application
    {
    public:
        void start();
        void run();
        void shutdown();

    private:
        GLFWwindow* m_window;
    };
}