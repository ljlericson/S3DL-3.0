#include "ShaderManager.h"

namespace Core
{
	namespace Manager
	{
		OpenGlBackend::Shader& ShaderManager::newShaderOrReference(const std::string& fPathVert, const std::string& fPathFrag)
		{
			if (!m_shaders.contains(fPathVert))
			{
				auto shad = std::make_unique<OpenGlBackend::Shader>(fPathVert, fPathFrag);
				shad->build();
				shad->attach();
				GLuint id = shad->getID(); // prevent use after move
				if (id != 0)
				{
					m_shaders.insert({
						fPathVert,
						std::move(shad)
					});
					m_idToString.insert({
						id,
						fPathVert
					});
					m_refCounts.insert({
						fPathVert,
						1
					});
				}
				else assert("Shader Failed to initialise or link");
			}
			else
			{
				std::print("INFO: Found existing shader...");
				m_refCounts.at(fPathVert)++;
				return *m_shaders.at(fPathVert);
			}
		}

		void ShaderManager::removeReference(OpenGlBackend::Shader& shad)
		{
			if (m_idToString.contains(shad.getID()))
			{
				const std::string& key = m_idToString.at(shad.getID());
				m_idToString.erase(shad.getID());
				if (--m_refCounts.at(key) == 0) // we know it must exist in ref count map
				{
					m_refCounts.erase(key);
					m_shaders.erase(key);
				}
			}
			else std::println("WARNING: No shader found within shader manager mathces input shader (ShaderManager::removeReference");
		}

		void ShaderManager::clear()
		{
			m_shaders.clear();
			m_refCounts.clear();
			m_idToString.clear();
		}
	}
}