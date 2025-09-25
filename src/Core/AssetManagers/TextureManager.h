#pragma once
#include <memory>
#include <unordered_map>
#include <assimp/scene.h>
#include <assert.h>
#include "../OpenGlBackend/texture.h"

namespace Core
{
	namespace Manager
	{
		// Manager for OpenGlBackend, but theoretically I could swith out
		// the opengl texture implementation with another but I won't
		// anytime soon

		class TextureManager
		{
		public:
			TextureManager();
			~TextureManager();

			std::shared_ptr<OpenGlBackend::Texture> newTexture(const aiTexture* texture, const std::string& texStr);
			std::shared_ptr<OpenGlBackend::Texture> newTexture(const std::string& fpath, GLuint target);

			std::shared_ptr<OpenGlBackend::Texture> getInvalidTex() const;
			GLuint getNumTextures() const;
			size_t getNumTexManagers() const;

		private:
			static inline uint32_t sm_numTextures = 0;
			static inline size_t sm_numActiveTexManagers = 0;
			static inline std::shared_ptr<OpenGlBackend::Texture> smp_invalidTex = nullptr;
			// valid textures
			std::unordered_map<std::string, std::shared_ptr<OpenGlBackend::Texture>> m_textures;
		};
	}
}