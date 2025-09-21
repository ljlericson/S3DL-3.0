#pragma once
#include <memory>
#include <unordered_map>
#include <assimp/scene.h>
#include <assert.h>
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

			std::shared_ptr<Texture> newTexture(const aiTexture* texture, const std::string& texStr);
			std::shared_ptr<Texture> newTexture(const std::string& fpath, GLuint target);

			std::shared_ptr<Texture> getInvalidTex() const;
			GLuint getNumTextures() const;
			size_t getNumTexManagers() const;

		private:
			static inline uint32_t sm_numTextures = 0;
			static inline size_t sm_numActiveTexManagers = 0;
			static inline std::shared_ptr<Texture> smp_invalidTex = nullptr;
			// valid textures
			std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
		};
	}
}