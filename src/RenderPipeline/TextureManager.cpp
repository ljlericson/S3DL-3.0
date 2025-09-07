#include "TextureManager.h"

GLuint Render::TextureManager::sm_numTextures = 0;

Render::TextureManager::~TextureManager()
{
	sm_numTextures -= (GLuint)m_textures.size();
	m_textures.clear();
}

Render::Texture* Render::TextureManager::newTexture(const aiTexture* texture, const std::string& texStr)
{
	// Check if texture already exists
	if(m_textures.find(texStr) != m_textures.end())
	{
		std::cout << "-----   Texture already exists...\n";
		return m_textures.at(texStr).get();
	}
	// Create new texture
	std::cout << "+++++   Creating new texture...\n";
	m_textures[texStr] = std::make_unique<Texture>(texture, sm_numTextures, texStr);
	if (!m_textures[texStr]->isValid())
	{
		m_textures.erase(texStr);
		m_textures[texStr] = std::make_unique<Texture>("assets/no_texture.png", sm_numTextures, GL_TEXTURE_2D);
	}
	else
	{
		m_numLocalTextures++;
		sm_numTextures++;
	}
	return m_textures.at(texStr).get();
}

Render::Texture* Render::TextureManager::newTexture(const std::string& fpath, GLuint target)
{
	// Check if texture already exists
	if (m_textures.find(fpath) != m_textures.end())
	{
		std::cout << "-----   Texture already exists...\n";
		return m_textures.at(fpath).get();
	}
	// Create new texture
	std::cout << "+++++   Creating new texture...\n";

	m_textures[fpath] = std::make_unique<Texture>(fpath.c_str(), sm_numTextures, target);
	if(!m_textures[fpath]->isValid())
	{
		m_textures.erase(fpath);
		m_textures[fpath] = std::make_unique<Texture>("assets/no_texture.png", sm_numTextures, target);
	}
	else
	{
		m_numLocalTextures++;
		sm_numTextures++;
	}
	return m_textures.at(fpath).get();
}

GLuint Render::TextureManager::getNumTextures() const
{
	return sm_numTextures;
}