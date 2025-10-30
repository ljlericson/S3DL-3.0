// slightly controversial I know
#include <assert.h>
// std lib
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <type_traits>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <vector>
// src file
#include "../BasicBackend/shader.h"
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
			enum class HotLoading
			{
				runOnDifferentThread,
				runOnSameThread
			};

		public:
			ShaderManager();

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			std::shared_ptr<T> newShaderOrGetShader(const std::string& fPathVert, const std::string& fPathFrag);

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			std::shared_ptr<T> getShader(const std::string& fPathVert);
			
			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			std::pair<std::string, std::string> getShaderFpath(BasicBackend::BasicShader* shad);

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			void reloadAll();

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			void reload(const std::string& key);

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
			bool hotReloadLoop();

			void doHotReloads(bool _do, ShaderManager::HotLoading specification);

			void clear();
		
		private:
			void hotReloadThread();

		private:
			bool m_runHotReloadsOnDiffThread;
			bool m_doHotReloads;
			bool m_checkHotReloads;
			std::thread* m_hotReloadThread = nullptr;
			std::vector<std::string> m_shadsToReload;

			std::unordered_map<std::string, std::shared_ptr<BasicBackend::BasicShader>> m_shaders;
			std::unordered_map<size_t, std::string> m_idToString;
			std::unordered_map<std::string, time_t> m_fragModTimes;
			std::unordered_map<std::string, time_t> m_vertModTimes;
			std::unordered_map<std::string, std::string> m_fragPaths;
		};
	}
}
