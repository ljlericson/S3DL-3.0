#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>


namespace Core
{
    namespace BasicBackend
    {
        class BasicShader
        {
        public:

            virtual ~BasicShader() = default;

            virtual void build() = 0;

            virtual void attach() = 0;

            virtual void use() const = 0;

            virtual void unuse() const = 0;

            virtual void setUniform(const std::string& name, int value) const = 0;

            virtual void setUniform(const std::string& name, glm::mat4 value) const = 0;

            virtual void reset() = 0;

            virtual uint32_t getID() const = 0;
        };
    }
}