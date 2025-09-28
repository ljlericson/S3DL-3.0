#include "ShaderManager.h"

namespace Core
{
	namespace Manager
	{
		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		std::shared_ptr<T> ShaderManager::newShaderOrGetShader(const std::string& fPathVert, const std::string& fPathFrag)
		{
			if (!m_shaders.contains(fPathVert))
			{
				std::ifstream fileVert(fPathVert);
				std::ifstream fileFrag(fPathFrag);
				
				std::string vertSrc, fragSrc;

				if (!fileVert || !fileFrag)
				{
					std::cout << "[ERROR]: Invalid file given to shader on init\n";
				}
				else
				{
					std::string lineFrag;
					while (std::getline(fileFrag, lineFrag))
						fragSrc += lineFrag + "\n";

					std::string lineVert;
					while (std::getline(fileVert, lineVert))
						vertSrc += lineVert + "\n";
				}

				auto shad = std::make_shared<T>(vertSrc.c_str(), fragSrc.c_str());
				shad->build();
				shad->attach();

				uint32_t id = shad->getID(); // prevent use after move
				if (id != 0)
				{
					struct stat fragStat, vertStat;
					if(stat(fPathVert.c_str(), &vertStat) != 0) assert("Shader Could not get stat time");
					if(stat(fPathFrag.c_str(), &fragStat) != 0) assert("Shader Could not get stat time");
					m_fragModTimes.insert({
						fPathVert,
						fragStat.st_mtime
						});
					m_vertModTimes.insert({
						fPathVert,
						vertStat.st_mtime
						});
					m_idToString.insert({
						shad->getID(),
						fPathVert
						});
					m_fragPaths.insert({
						fPathVert,
						fPathFrag
						});
					m_shaders.insert({
						fPathVert,
						shad
						});
					return shad;
				}
				else { assert("Shader Failed to initialise or link"); /* no return because program aborts */ return std::dynamic_pointer_cast<T>(m_shaders.at(fPathVert)); /* just to get rid of the compiler warning */; }
			}
			else
			{
				std::print("INFO: Found existing shader...");
				return std::dynamic_pointer_cast<T>(m_shaders.at(fPathVert));
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		std::shared_ptr<T> ShaderManager::getShader(const std::string& fPathVert)
		{
			if (m_shaders.contains(fPathVert))
			{
				return std::dynamic_pointer_cast<T>(m_shaders.at(fPathVert));
			}
			else
			{
				assert("NO SHADER FOUND ShaderManager::getShader");
				return nullptr;
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		void ShaderManager::reloadAll()
		{
			for (auto& [key, shad] : m_shaders)
			{
				uint32_t idBefore = shad->getID();
				struct stat fragStat, vertStat;
				if (stat(key.c_str(), &vertStat) != 0) assert("Shader Could not get stat time");
				if (stat(m_fragPaths.at(key).c_str(), &fragStat) != 0) assert("Shader Could not get stat time");

				if (fragStat.st_mtime > m_fragModTimes.at(key) || vertStat.st_mtime > m_vertModTimes.at(key))
				{
					std::ifstream fileVert(key.c_str());
					std::ifstream fileFrag(m_fragPaths.at(key).c_str());

					std::string vertSrc, fragSrc;

					if (!fileVert || !fileFrag)
					{
						std::cout << "[ERROR]: Invalid file given to shader on init\n";
					}
					else
					{
						std::string lineFrag;
						while (std::getline(fileFrag, lineFrag))
							fragSrc += lineFrag + "\n";

						std::string lineVert;
						while (std::getline(fileVert, lineVert))
							vertSrc += lineVert + "\n";
					}

					shad->reset();
					shad = std::make_shared<T>( vertSrc.c_str(), fragSrc.c_str() );
					shad->build();
					shad->attach();

					m_idToString.erase(m_idToString.find(idBefore));
					m_idToString.insert({
						shad->getID(),
						key
					});
				}
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		void ShaderManager::reload(const std::string& key)
		{
			if(m_shaders.contains(key))
			{
				auto& shad = m_shaders.at(key);
				uint32_t idBefore = shad->getID();
				std::ifstream fileVert(key.c_str());
				std::ifstream fileFrag(m_fragPaths.at(key).c_str());

				std::string vertSrc, fragSrc;

				if (!fileVert || !fileFrag)
				{
					std::cout << "[ERROR]: Invalid file given to shader on init\n";
				}
				else
				{
					std::string lineFrag;
					while (std::getline(fileFrag, lineFrag))
						fragSrc += lineFrag + "\n";

					std::string lineVert;
					while (std::getline(fileVert, lineVert))
						vertSrc += lineVert + "\n";
				}

				shad->reset();
				shad = std::make_shared<T>( vertSrc.c_str(), fragSrc.c_str() );
				shad->build();
				shad->attach();

				m_idToString.erase(m_idToString.find(idBefore));
				m_idToString.insert({
					shad->getID(),
					key
				});
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		std::pair<std::string, std::string> ShaderManager::getShaderFpath(BasicBackend::BasicShader* shad)
		{
			if (m_idToString.contains(shad->getID()))
			{
				return {
					m_idToString.at(shad->getID()),
					m_fragPaths.at(m_idToString.at(shad->getID())) // using the vertex shader's path as key
				};
			}
			assert("no shader found shaderman::getshaderfpath()");
			return { "123", "123" };
		}

		void ShaderManager::doHotReloads(bool _do)
		{
			m_checkHotReloads = _do;
			if (!m_checkHotReloads)
			{
				if(m_hotReloadThread && m_hotReloadThread->joinable())
				{
					m_hotReloadThread->join();
					if (m_hotReloadThread)
						delete m_hotReloadThread;
				}
			}
			else
			{
				m_hotReloadThread = new std::thread{ &Core::Manager::ShaderManager::hotReloadThread, this };
				m_doHotReloads = true;
				m_checkHotReloads = true;
			}
		}

		void ShaderManager::hotReloadThread()
		{
			using namespace std::chrono_literals;
			while (m_checkHotReloads)
			{
				if (m_doHotReloads)
				{
					for(const auto& [key, shad] :m_shaders)
					{
						struct stat fragStat1, vertStat1;

						if (stat(key.c_str(), &vertStat1) != 0) assert("Shader Could not get stat time");
						if (stat(m_fragPaths.at(key).c_str(), &fragStat1) != 0) assert("Shader Could not get stat time");

						if (m_fragModTimes.at(key) < fragStat1.st_mtime || m_vertModTimes.at(key) < vertStat1.st_mtime)
						{
							m_fragModTimes.at(key) = fragStat1.st_mtime;
							m_vertModTimes.at(key) = vertStat1.st_mtime;
							m_shadsToReload.push_back(key);
							m_doHotReloads = false;
						}
						std::this_thread::sleep_for(50ms);
					}
				}
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicShader, T>
		bool ShaderManager::hotReloadLoop()
		{
			bool reloadedOne = false;
			if(m_checkHotReloads)
			{
				for (const std::string& key : m_shadsToReload)
				{
					std::print("\nDETECTED SHADER CHANGE TO {}\n", key);
					this->reload<T>(key);
					m_doHotReloads = true;
					reloadedOne = true;
				}
				m_shadsToReload.clear();
			}
			return reloadedOne;
		}

		void ShaderManager::clear()
		{
			m_shaders.clear();
		}

		template std::shared_ptr<OpenGlBackend::Shader> ShaderManager::newShaderOrGetShader<OpenGlBackend::Shader>(const std::string&, const std::string&);

		template void ShaderManager::reloadAll<Core::OpenGlBackend::Shader>();

		template std::shared_ptr<Core::OpenGlBackend::Shader>  ShaderManager::getShader<Core::OpenGlBackend::Shader>(const std::string&);

		template std::pair<std::string, std::string> ShaderManager::getShaderFpath<OpenGlBackend::Shader>(BasicBackend::BasicShader*);

		template void ShaderManager::reload<OpenGlBackend::Shader>(const std::string&);

		template bool ShaderManager::hotReloadLoop<OpenGlBackend::Shader>();
	}
}