#include "AssetManager.h"

namespace Core
{
	namespace Manager
	{
		AssetManager::AssetManager()
			:
			m_modelManager{ std::make_unique<ModelManager>() },
			m_texManager{ std::make_unique<TextureManager>() },
			m_shadManager{ std::make_unique<ShaderManager>() },
			m_audioBufferManager{ std::make_unique<AudioBufferManager>() }
		{	}

		[[nodiscard]] ModelManager* AssetManager::getModelManager() const				{ return m_modelManager.get(); }
		[[nodiscard]] TextureManager* AssetManager::getTextureManager() const			{ return m_texManager.get(); }
		[[nodiscard]] ShaderManager* AssetManager::getShadManager() const				{ return m_shadManager.get(); }
		[[nodiscard]] AudioBufferManager* AssetManager::getAudioBufferManager() const   { return m_audioBufferManager.get(); }
	}
}