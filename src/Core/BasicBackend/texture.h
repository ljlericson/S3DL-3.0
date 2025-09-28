#pragma once
#include <iostream>
#include <filesystem>
#include <string>
// external libs
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Core
{
    namespace BasicBackend
    {
        class BasicTexture
        {
        public:
            virtual ~BasicTexture() = default;

            // Core API
            virtual void bind() const = 0;

            virtual void unbind() const = 0;

            virtual void setParam(uint32_t pname, uint32_t param) = 0;

            virtual void uniform(uint32_t shadProgram, const char* uName) const = 0;

            virtual bool isValid() const = 0;

            virtual void _delte() = 0;

            virtual uint32_t getID() const = 0;

        protected:
            BasicTexture() = default;
            BasicTexture(const char* /*fpath*/, uint32_t /*texUnit*/, uint32_t /*target*/) {}
            BasicTexture(const aiTexture* /*tex*/, uint32_t /*texUnit*/, const std::string& /*texSrc*/) {}
        };
    }
}