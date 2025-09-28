#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Core
{
    namespace OpenGlBackend
    {
        class Shader
        {
        public:

            Shader();
            Shader(const char* vertSrc, const char* fragScr);
            ~Shader();

            void build();

            void attach();

            void use() const;

            void unuse() const;

            void setUniform(const std::string& name, int value) const;

            void setUniform(const std::string& name, glm::mat4 value) const;
            
            void reset();

            GLuint getID() const;

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