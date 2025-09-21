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

            // underscore before to ensure it is at the bottom
            // of the member list
            void _delte();

            GLuint getID() const;
        };
    }
}