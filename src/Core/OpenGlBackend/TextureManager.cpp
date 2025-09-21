#include "TextureManager.h"

namespace Core
{
	namespace OpenGlBackend
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
				std::cout << "No texture managers exist, deleting smp_invalidTex\n";
				delete smp_invalidTex;
			}
		}

		Texture* TextureManager::newTexture(const aiTexture* texture, const std::string& texStr)
		{
			// Check if texture already exists
			if (m_textures.find(texStr) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return m_textures.at(texStr).get();
			}

			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			auto tex = std::make_unique<Texture>(texture, sm_numTextures + 1, texStr);
			if (!tex->isValid())
			{
				return this->getInvalidTex();
			}
			else
			{
				sm_numTextures++;
				m_textures[texStr] = std::move(tex);
			}

			return m_textures.at(texStr).get();
		}

		Texture* TextureManager::newTexture(const std::string& fpath, GLuint target)
		{
			// Check if texture already exists
			if (m_textures.find(fpath) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return m_textures.at(fpath).get();
			}
			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			// create texture from params passed
			auto tex = std::make_unique<Texture>(fpath.c_str(), sm_numTextures + 1, target);
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

			return m_textures.at(fpath).get();
		}

		Texture* TextureManager::getInvalidTex() const
		{
			if (!smp_invalidTex)
			{
				sm_numTextures++;
				smp_invalidTex = new Texture("assets/no_texture.png", sm_numTextures, GL_TEXTURE_2D);
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