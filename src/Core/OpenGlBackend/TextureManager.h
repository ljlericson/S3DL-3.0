#pragma once
#include <memory>
#include <unordered_map>
#include <assimp/scene.h>
#include "texture.h"

namespace Core
{
	namespace OpenGlBackend
	{
		class TextureManager
		{
		public:
			TextureManager();
			~TextureManager();

			Texture* newTexture(const aiTexture* texture, const std::string& texStr);
			Texture* newTexture(const std::string& fpath, GLuint target);

			Texture* getInvalidTex() const;
			GLuint getNumTextures() const;
			size_t getNumTexManagers() const;

		private:
			static inline uint32_t sm_numTextures = 0;
			static inline size_t sm_numActiveTexManagers = 0;
			static inline Texture* smp_invalidTex = nullptr;
			// valid textures
			std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
		};
	}
}