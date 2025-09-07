#pragma once
#include <memory>
#include <unordered_map>
#include <assimp/scene.h>
#include "texture.h"


namespace Render
{
	class TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager();
		
		Texture* newTexture(const aiTexture* texture, const std::string& texStr);
		Texture* newTexture(const std::string& fpath, GLuint target);

		GLuint getNumTextures() const;
	private:
		static GLuint sm_numTextures;
		GLuint m_numLocalTextures = 0;
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
	};
}