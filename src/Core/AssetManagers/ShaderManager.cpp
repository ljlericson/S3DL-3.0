#include "ShaderManager.h"

namespace Core
{
	namespace Manager
	{
		std::shared_ptr<OpenGlBackend::Shader> ShaderManager::newShaderOrGetShader(const std::string& fPathVert, const std::string& fPathFrag)
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

				auto shad = std::make_unique<OpenGlBackend::Shader>(vertSrc.c_str(), fragSrc.c_str());
				shad->build();
				shad->attach();

				GLuint id = shad->getID(); // prevent use after move
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
						std::move(shad)
						});
					return m_shaders.at(fPathVert);
				}
				else {assert("Shader Failed to initialise or link"); /* no return because program aborts */ return m_shaders.at(std::string("")) /* just to get rid of the compiler warning */; }
			}
			else
			{
				std::print("INFO: Found existing shader...");
				return m_shaders.at(fPathVert);
			}
		}

		std::shared_ptr<OpenGlBackend::Shader> ShaderManager::getShader(const std::string& fPathVert)
		{
			if (m_shaders.contains(fPathVert))
			{
				return m_shaders.at(fPathVert);
			}
			else
			{
				assert("NO SHADER FOUND ShaderManager::getShader");
				return nullptr;
			}
		}

		void ShaderManager::hotReloadAll()
		{
			for (const auto& [key, shad] : m_shaders)
			{
				GLuint idBefore = shad->getID();
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

					*shad = OpenGlBackend::Shader{ vertSrc.c_str(), fragSrc.c_str()};
					shad->build();
					shad->attach();

					m_idToString.insert({
						shad->getID(),
						key
						});
					m_idToString.erase(m_idToString.find(idBefore));
				}
			}
		}

		void ShaderManager::hotReload(const std::string& key)
		{
			if(m_shaders.contains(key))
			{
				struct stat fragStat, vertStat;
				auto shad = m_shaders.at(key);
				GLuint idBefore = shad->getID();

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

					*shad = OpenGlBackend::Shader{ vertSrc.c_str(), fragSrc.c_str() };
					shad->build();
					shad->attach();

					m_idToString.insert({
						shad->getID(),
						key
						});
					m_idToString.erase(m_idToString.find(idBefore));
				}
			}
		}

		std::pair<std::string, std::string> ShaderManager::getShaderFpath(OpenGlBackend::Shader* shad)
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

		void ShaderManager::clear()
		{
			m_shaders.clear();
		}
	}
}