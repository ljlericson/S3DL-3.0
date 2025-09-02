#include "texture.h"

Render::Texture::Texture() 
    : m_id(0), m_texUnit(-1), m_target(0)  {  }

Render::Texture::Texture(const char* fpath, GLuint texUnit, GLuint target)
    : m_texUnit(texUnit), m_target(target), m_id(0)
{
    // texture info for loading
    int width,
        height,
        numColChan;
    // texture bytes
    std::filesystem::path normPath = std::filesystem::path(fpath).lexically_normal();
    std::string finalPath = normPath.string();

    if (!std::filesystem::exists(normPath)) {
        std::cerr << "[ERROR]: File does not exist at: " << finalPath << "\n";
    }

    uint8_t* bytes = stbi_load(finalPath.c_str(), &width, &height, &numColChan, 0);
    if(!bytes)
    {
        std::cout << "[ERROR]: Could not load texture image \"" << fpath << "\", error: " << stbi_failure_reason() << "\n";
    }
    else
    {
		// generate and bind texture
        glGenTextures(1, &m_id);
        glActiveTexture(GL_TEXTURE0 + m_texUnit);
        glBindTexture(m_target, m_id);

		// set texture parameters (wrapping and filtering)
        GLenum format = (numColChan == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(m_target);
        stbi_image_free(bytes);

		// unbind texture after loading
		glBindTexture(m_target, 0);
    }
}

Render::Texture::Texture(aiTexture* tex, GLuint texUnit, const std::string& texSrc)
    : m_texUnit(texUnit), m_target(GL_TEXTURE_2D), m_id(0)
{
    if (!tex) {
        std::cout << "[ERROR]: Null embedded texture pointer\n";
        return;
    }

    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0 + m_texUnit);
    glBindTexture(m_target, m_id);

    int width = 0, height = 0, numColChan = 0;
    unsigned char* bytes = nullptr;

    if (tex->mHeight == 0) {
        // Compressed format (embedded as a blob, e.g. PNG/JPG)
        bytes = stbi_load_from_memory(
            reinterpret_cast<unsigned char*>(tex->pcData),
            tex->mWidth,
            &width, &height, &numColChan, 0
        );
    }
    else {
        // Raw pixel data (uncompressed)
        width = tex->mWidth;
        height = tex->mHeight;
        numColChan = 4; // aiTexture::pcData stores BGRA
        bytes = reinterpret_cast<unsigned char*>(tex->pcData);
    }

    if (!bytes) {
        std::cout << "[ERROR]: Could not load embedded texture \"" << texSrc
            << "\", error: " << stbi_failure_reason() << "\n";
    }
    else {
        GLenum format = (numColChan == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(m_target, 0, format, width, height, 0,
            format, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(m_target);

        if (tex->mHeight == 0) {
            stbi_image_free(bytes); // only free if stb allocated it
        }
    }

    glBindTexture(m_target, 0);
}

void Render::Texture::setParam(GLuint pname, GLuint params)
{
    glBindTexture(m_target, m_id); // ensure texture is bound before setting parameters
    glTexParameteri(m_target, pname, params);
    // unbind texture after loading
    glBindTexture(m_target, 0);
}

void Render::Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0 + m_texUnit);
    glBindTexture(m_target, m_id);
}

void Render::Texture::uniform(GLuint shadProgram, const char* uName) const
{
    glUseProgram(shadProgram);
    GLint loc = glGetUniformLocation(shadProgram, uName);
    if (loc == -1 && false) // disable this shit because it is annoying af
    {
        std::cerr << "[ERROR]: Texture uniform not found!\n";
    }
    else
    {
        glUniform1i(loc, m_texUnit);
    }
}

void Render::Texture::unbind() const
{
    glBindTexture(m_target, 0);
}

void Render::Texture::_freeTexBuffer()
{
    if(m_id != 0)
        glDeleteTextures(1, &m_id);
}

Render::Texture::~Texture()
{
    _freeTexBuffer();
}
