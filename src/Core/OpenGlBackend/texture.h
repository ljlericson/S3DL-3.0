#pragma once
#include <iostream>
#include <filesystem>
// external libs
#include <glad/glad.h>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Core
{
    namespace OpenGlBackend
    {
        class Texture
        {
        private:
            GLuint m_id;
            GLuint m_target;
            GLuint m_texUnit;
            bool m_isLoaded;

        public:
            Texture();
            Texture(const char* fpath, GLuint texUnit, GLuint target);
            Texture(const aiTexture*, GLuint texUnit, const std::string& texSrc);
            ~Texture();

            void setParam(GLuint pname, GLuint params);

            void bind() const;

            void uniform(GLuint shadProgram, const char* uName) const;

            void unbind() const;

            bool isValid() const;

            void _freeTexBuffer();

            GLuint getID() const;
        };
    }
}