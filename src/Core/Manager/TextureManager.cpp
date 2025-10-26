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
			sm_numTextures -= (uint32_t)m_textures.size();
			m_textures.clear();
			sm_numActiveTexManagers--;
			if (sm_numActiveTexManagers == 0)
			{
				sm_numTextures = 0;
			}
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
		std::shared_ptr<T> TextureManager::newTexture(const aiTexture* texture, const std::string& texStr, ReturnOnError specification)
		{
			// Check if texture already exists
			if (m_textures.find(texStr) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return std::dynamic_pointer_cast<T>(m_textures.at(texStr));
			}

			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			auto tex = std::make_shared<T>(texture, sm_numTextures + 1, texStr);
			if (!tex->isValid())
			{
				return (specification == ReturnOnError::returnNullptr) ? nullptr : this->getInvalidTex<T>();
			}
			else
			{
				sm_numTextures++;
				m_textures[texStr] = std::move(tex);
			}

			return std::dynamic_pointer_cast<T>(m_textures.at(texStr));
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
		std::shared_ptr<T> TextureManager::newTexture(const std::string& fpath, uint32_t target, ReturnOnError specification)
		{
			// Check if texture already exists
			if (m_textures.find(fpath) != m_textures.end())
			{
				std::cout << "-----   Texture already exists...\n";
				return std::dynamic_pointer_cast<T>(m_textures.at(fpath));
			}
			// Create new texture
			std::cout << "+++++   Creating new texture...\n";

			// create texture from params passed
			auto tex = std::make_unique<T>(fpath.c_str(), sm_numTextures + 1, target);
			// check texture valid
			if (!m_textures[fpath]->isValid())
			{
				// if not return the static invalid
				// texture
				return (specification == ReturnOnError::returnNullptr) ? nullptr : this->getInvalidTex<T>();
			}
			else
			{
				// else we incremement to the num
				// of textures and asign to new
				// map entry
				sm_numTextures++;
				m_textures.insert({ fpath, std::move(tex) });
			}

			return std::dynamic_pointer_cast<T>(m_textures.at(fpath));
		}

		template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
		std::shared_ptr<T> TextureManager::getInvalidTex() const
		{
			if (!smp_invalidTex)
			{
				sm_numTextures++;
				smp_invalidTex = std::make_shared<T>("assets/no_texture.png", sm_numTextures, GL_TEXTURE_2D);
			}
			return std::dynamic_pointer_cast<T>(smp_invalidTex);
		}

		uint32_t TextureManager::getNumTextures() const
		{
			return (uint32_t)m_textures.size();
		}

		size_t TextureManager::getNumTexManagers() const
		{
			return sm_numActiveTexManagers;
		}

		template std::shared_ptr<OpenGlBackend::Texture> TextureManager::newTexture(const aiTexture*, const std::string&, ReturnOnError);

		template std::shared_ptr<OpenGlBackend::Texture> TextureManager::newTexture(const std::string&, uint32_t, ReturnOnError);

		template std::shared_ptr<OpenGlBackend::Texture> TextureManager::getInvalidTex() const;
	}
} 