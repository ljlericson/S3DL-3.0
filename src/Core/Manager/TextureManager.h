#pragma once
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <assimp/scene.h>
#include <assert.h>
#include "../BasicBackend/texture.h"
#include "../OpenGlBackend/texture.h"

namespace Core
{
	namespace Manager
	{
		class TextureManager
		{
		public:
			enum class ReturnOnError
			{
				returnInvalidTexture,
				returnNullptr
			};
		public:
			TextureManager();
			~TextureManager();

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
			std::shared_ptr<T> newTexture(const aiTexture* texture, const std::string& texStr, ReturnOnError specification);

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
			std::shared_ptr<T> newTexture(const std::string& fpath, uint32_t target, ReturnOnError specification);

			template<typename T> requires std::is_base_of_v<BasicBackend::BasicTexture, T>
			std::shared_ptr<T> getInvalidTex() const;

			uint32_t getNumTextures() const;
			size_t getNumTexManagers() const;

		private:
			static inline uint32_t sm_numTextures = 0;
			static inline size_t sm_numActiveTexManagers = 0;
			static inline std::shared_ptr<BasicBackend::BasicTexture> smp_invalidTex = nullptr;
			// valid textures
			std::unordered_map<std::string, std::shared_ptr<BasicBackend::BasicTexture>> m_textures;
		};
	}
}