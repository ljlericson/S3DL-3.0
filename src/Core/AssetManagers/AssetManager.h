#include <memory>
#include <unordered_map>

#include "TextureManager.h"
#include "AudioBufferStorage.h"
#include "ModelManager.h"
#include "ShaderManager.h"

namespace Core
{
	namespace Manager
	{
		class AssetManager
		{
		public:
			AssetManager();
			AssetManager(AssetManager&&) noexcept = default;
			AssetManager(const AssetManager&) = delete;
			AssetManager& operator=(const AssetManager&) = delete;
			AssetManager& operator=(AssetManager&&) noexcept = default;

			ModelManager* getModelManager() const;
			TextureManager* getTextureManager() const;
			ShaderManager* getShadManager() const;
			AudioBufferManager* getAudioBufferManager() const;

		private:
			std::unique_ptr<ModelManager>        m_modelManager;
			std::unique_ptr<TextureManager>      m_texManager;
			std::unique_ptr<ShaderManager>       m_shadManager;
			std::unique_ptr<AudioBufferManager>  m_audioBufferManager;
		};
	}
}