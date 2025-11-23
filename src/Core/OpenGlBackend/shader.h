#pragma once
#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../BasicBackend/shader.h"


namespace Core
{
    namespace OpenGlBackend
    {
        class Shader : public BasicBackend::BasicShader
        {
        public:

            Shader();
            Shader(const char* vertSrc, const char* fragScr);
            ~Shader() override;

            void build() override;

            void attach() override;

            void use() const override;

            void unuse() const override;

            void setUniform(const std::string& name, int value, UniformWarningType specification) const override;

            void setUniform(const std::string& name, glm::mat4 value, UniformWarningType specification) const override;

            void setUniform(const std::string& name, float value, UniformWarningType specification) const override;

            void setUniform(const std::string& name, glm::vec3 value, UniformWarningType specification) const override;

            void setUniform(const std::string& name, bool value, UniformWarningType specification) const override;
    
            void reset() override;

            GLuint getID() const override;

        private:
            bool m_init, m_linked;
            GLuint m_idFrag;
            GLuint m_idVert;
            std::string m_fragSrc;
            std::string m_vertSrc;
            GLuint m_id;
        };
    }
}