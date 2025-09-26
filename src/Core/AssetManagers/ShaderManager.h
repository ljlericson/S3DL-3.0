// slightly controversial I know
#include <assert.h>
// std lib
#include <print>
#include <string>
#include <memory>
#include <unordered_map>
// src file
#include "../OpenGlBackend/shader.h"

namespace Core
{
	namespace Manager
	{
		// technically a ShaderManager for my opengl impl but theoritically it could be used with any impl
		// which is why it isn't part of my gl backend

		class ShaderManager 
		{
		public:
			ShaderManager() = default;

			OpenGlBackend::Shader& newShaderOrReference(const std::string& fPathVert, const std::string& fPathFrag);

			void removeReference(OpenGlBackend::Shader& shad);

			void clear();

		private:
			std::unordered_map<std::string, std::unique_ptr<OpenGlBackend::Shader>> m_shaders;
			std::unordered_map<GLuint, std::string> m_idToString;
			std::unordered_map<std::string, size_t> m_refCounts;
		};
	}
}