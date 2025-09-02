#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string_view>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Render
{
    class Shader
    {
    public:

        Shader();
        Shader(std::string_view fpathVert, std::string_view fpathFrag);
		~Shader();

        void build();

        void attach();

        void use() const;

        void unuse() const;

		void setUniform(const std::string& name, int value) const;

        void setUniform(const std::string& name, glm::mat4 value) const;

        GLuint getID() const;

    private:
        bool m_init, m_linked;
        GLuint m_idFrag;
        GLuint m_idVert;
        std::string m_fragSrc;
        std::string m_vertSrc;
        GLuint m_id;
    }; 
};