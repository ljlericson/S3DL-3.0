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

			ModelManager* getModelManager() const;
			TextureManager* getTextureManager() const;
			ShaderManager* getShadManager() const;
			AudioBufferManager* getAudioBufferManager() const;

		private:
			std::unique_ptr<ModelManager>        m_modelManager = nullptr;
			std::unique_ptr<TextureManager>      m_texManager = nullptr;
			std::unique_ptr<ShaderManager>       m_shadManager = nullptr;
			std::unique_ptr<AudioBufferManager>  m_audioBufferManager = nullptr;
		};
	}
}