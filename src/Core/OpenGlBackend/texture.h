#pragma once
#include <iostream>
#include <filesystem>
// external libs
#include <glad/glad.h>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../BasicBackend/texture.h"

namespace Core
{
    namespace OpenGlBackend
    {
        class Texture : public BasicBackend::BasicTexture
        {
        private:
            GLuint m_id;
            GLuint m_target;
            GLuint m_texUnit;

        public:
            Texture();
            Texture(const char* fpath, GLuint texUnit, GLuint target);
            Texture(const aiTexture* tex, GLuint texUnit, const std::string& texSrc);
            ~Texture() override;

            void bind() const override;

            void unbind() const override;

            void setParam(GLuint pname, GLuint params) override;

            void uniform(GLuint shadProgram, const char* uName) const override;

            bool isValid() const override;

            void _delte() override;

            GLuint getID() const override;
        };
    }
}