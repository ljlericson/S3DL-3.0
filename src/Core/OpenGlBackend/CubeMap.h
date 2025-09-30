#pragma once
#include <array>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <stb_image.h>
#include <glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "shader.h"
#include "camera.h"
#include "../../Utils/Utils.h"

namespace Core::OpenGlBackend
{
	// |---- IMPORTANT ----------------------------|
	// Most if not all of the code in this class was
	// written by https://github.com/VictorGordan/

	class CubeMap
	{
	public:
		CubeMap(const char* texFpath1,
				const char* texFpath2,
				const char* texFpath3,
				const char* texFpath4,
				const char* texFpath5,
				const char* texFpath6);

		void draw(Shader* shad, Camera* cam);
	
	private:
		std::array<float, 24> m_verts;
		std::array<int, 36> m_inds;

		glm::mat4 m_view;
		glm::mat4 m_projection;

		uint32_t m_vao;
		uint32_t m_vbo;
		uint32_t m_ebo;

		uint32_t m_tex;
	};
}