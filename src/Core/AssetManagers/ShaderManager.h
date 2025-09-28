// slightly controversial I know
#include <assert.h>
// std lib
#pragma once
#include <print>
#include <string>
#include <memory>
#include <unordered_map>
#include <sys/stat.h>
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

			std::shared_ptr<OpenGlBackend::Shader> newShaderOrGetShader(const std::string& fPathVert, const std::string& fPathFrag);

			std::shared_ptr<OpenGlBackend::Shader> getShader(const std::string& fPathVert);
			
			std::pair<std::string, std::string> getShaderFpath(OpenGlBackend::Shader* shad);

			void hotReloadAll();

			void hotReload(const std::string& key);

			void clear();

		private:
			std::unordered_map<std::string, std::shared_ptr<OpenGlBackend::Shader>> m_shaders;
			std::unordered_map<size_t, std::string> m_idToString;
			std::unordered_map<std::string, time_t> m_fragModTimes;
			std::unordered_map<std::string, time_t> m_vertModTimes;
			std::unordered_map<std::string, std::string> m_fragPaths;
		};
	}
}