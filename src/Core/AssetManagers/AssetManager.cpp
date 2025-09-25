#include "AssetManager.h"

namespace Core
{
	namespace Manager
	{

		ModelManager* AssetManager::getModelManager() const				{ return m_modelManager.get(); }
		TextureManager* AssetManager::getTextureManager() const			{ return m_texManager.get(); }
		ShaderManager* AssetManager::getShadManager() const				{ return m_shadManager.get(); }
		AudioBufferManager* AssetManager::getAudioBufferManager() const { return m_audioBufferManager.get(); }
	}
}