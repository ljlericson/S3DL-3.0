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

Render::Texture::Texture(const aiTexture* tex, GLuint texUnit, const std::string& texSrc)
    : m_texUnit(texUnit), m_target(GL_TEXTURE_2D), m_id(0)
{
    if (!tex) {
        std::cerr << "[ERROR]: Null embedded texture pointer for source \"" << texSrc << "\"\n";
        return;
    }

    // Generate texture object
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0 + m_texUnit);
    glBindTexture(m_target, m_id);

    int width = 0, height = 0, numColChan = 0;
    unsigned char* bytes = nullptr;

    if (tex->mHeight == 0) {
        // Case 1: Compressed (e.g. PNG or JPG stored in memory)
        bytes = stbi_load_from_memory(
            reinterpret_cast<unsigned char*>(tex->pcData),
            tex->mWidth, // length in bytes
            &width, &height, &numColChan, 0
        );

        if (!bytes) {
            std::cerr << "[ERROR]: Could not decode embedded compressed texture \""
                << texSrc << "\", stb error: " << stbi_failure_reason() << "\n";
            glBindTexture(m_target, 0);
            return;
        }

        GLenum format = (numColChan == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, width, height, 0,
            format, GL_UNSIGNED_BYTE, bytes);

        stbi_image_free(bytes); // stb allocated memory
    }
    else {
        // Case 2: Uncompressed raw data (BGRA format from Assimp)
        width = tex->mWidth;
        height = tex->mHeight;
        numColChan = 4; // Assimp guarantees BGRA for aiTexel

        bytes = reinterpret_cast<unsigned char*>(tex->pcData);

        glTexImage2D(m_target, 0, GL_RGBA, width, height, 0,
            GL_BGRA, GL_UNSIGNED_BYTE, bytes);
        // no free: Assimp owns this memory
    }

    glGenerateMipmap(m_target);

    // Set safe default parameters
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

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
    if (loc == -1 && true ) // sometimes disable this error because its annoyings
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
    std::cout << "texture deleted\n";
    if(m_id != 0)
        glDeleteTextures(1, &m_id);
}

bool Render::Texture::isValid() const
{
    return m_id != 0;
}

Render::Texture::~Texture()
{
    _freeTexBuffer();
}
