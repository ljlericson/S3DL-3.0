#include "TextureManager.h"

namespace Core
{
	namespace Manager
	{
		TextureManager::TextureManager()
		{
			sm_numActiveTexManagers++;
		}

		TextureManager::~TextureManager()
		{
			sm_numTextures -= (GLuint)m_textures.size();
			m_textures.clear();
			sm_numActiveTexManagers--;
			if (sm_numActiveTexManagers == 0)
			{
				sm_numTextures = 0;
			}
		}

		std::shared_ptr<OpenGlBackend::Texture> TextureManager::newTexture(const aiTexture* texture, const std::string& texStr)
		{
			// Check if texture already exists
			if (m_textures.find(texStr) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return m_textures.at(texStr);
			}

			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			auto tex = std::make_shared<OpenGlBackend::Texture>(texture, sm_numTextures + 1, texStr);
			if (!tex->isValid())
			{
				return this->getInvalidTex();
			}
			else
			{
				sm_numTextures++;
				m_textures[texStr] = std::move(tex);
			}

			return m_textures.at(texStr);
		}

		std::shared_ptr<OpenGlBackend::Texture> TextureManager::newTexture(const std::string& fpath, GLuint target)
		{
			// Check if texture already exists
			if (m_textures.find(fpath) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return m_textures.at(fpath);
			}
			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			// create texture from params passed
			auto tex = std::make_unique<OpenGlBackend::Texture>(fpath.c_str(), sm_numTextures + 1, target);
			// check texture valid
			if (!m_textures[fpath]->isValid())
			{
				// if not return the static invalid
				// texture
				return this->getInvalidTex();
			}
			else
			{
				// else we incremement to the num
				// of textures and asign to new
				// map entry
				sm_numTextures++;
				m_textures.insert({ fpath, std::move(tex) });
			}

			return m_textures.at(fpath);
		}

		std::shared_ptr<OpenGlBackend::Texture> TextureManager::getInvalidTex() const
		{
			if (!smp_invalidTex)
			{
				sm_numTextures++;
				smp_invalidTex = std::make_shared<OpenGlBackend::Texture>("assets/no_texture.png", sm_numTextures, GL_TEXTURE_2D);
			}
			return smp_invalidTex;
		}

		GLuint TextureManager::getNumTextures() const
		{
			return (GLuint)m_textures.size();
		}

		size_t TextureManager::getNumTexManagers() const
		{
			return sm_numActiveTexManagers;
		}
	}
}