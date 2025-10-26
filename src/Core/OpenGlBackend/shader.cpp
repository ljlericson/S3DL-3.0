#include "shader.h"

namespace Core
{
    namespace OpenGlBackend
    {
        Shader::Shader()
            : m_init(false), m_linked(false), m_id(0), m_idFrag(0), m_idVert(0), m_fragSrc{ "" }, m_vertSrc{ "" }
        {
        }

        Shader::Shader(const char* vertSrc, const char* fragSrc)
            : m_init(true), m_linked(false), m_id(0), m_idFrag(0), m_idVert(0), m_fragSrc{ fragSrc }, m_vertSrc{ vertSrc }
        {  }


        Shader::~Shader()
        {
            if (m_init && m_linked)
                glDeleteProgram(m_id);
        }

        void Shader::build()
        {
            if (m_init)
            {
                // create program id
                m_id = glCreateProgram();

                // get new id
                m_idFrag = glCreateShader(GL_FRAGMENT_SHADER);
                // compile fragment shader
                const GLchar* fragSrc = m_fragSrc.c_str();
                glShaderSource(m_idFrag, 1, &fragSrc, NULL);
                glCompileShader(m_idFrag);
                // error checking
                GLint success;
                glGetShaderiv(m_idFrag, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    char infoLog[512];
                    glGetShaderInfoLog(m_idFrag, 512, NULL, infoLog);
                    std::cout << "[ERROR]: Fragment shader:\n" << m_fragSrc << "compilation failed\n" << infoLog << "\n";
                }

                // get new id
                m_idVert = glCreateShader(GL_VERTEX_SHADER);
                // compile vertex shader
                const GLchar* vertSrc = m_vertSrc.c_str();
                glShaderSource(m_idVert, 1, &vertSrc, NULL);
                glCompileShader(m_idVert);
                // error checking
                GLint success2;
                glGetShaderiv(m_idFrag, GL_COMPILE_STATUS, &success2);
                if (!success2)
                {
                    char infoLog[512];
                    glGetShaderInfoLog(m_idFrag, 512, NULL, infoLog);
                    std::cout << "[ERROR]: Fragment shader compilation failed\n" << infoLog << "\n";
                }

                m_fragSrc.clear();
                m_vertSrc.clear();
            }
            else
            {
                std::cout << "[ERROR]: Shader must be initialised before attempting to build\n";
            }
        }

        void Shader::attach()
        {
            if (m_init)
            {
                glAttachShader(m_id, m_idFrag);
                glAttachShader(m_id, m_idVert);
                glLinkProgram(m_id);

                GLint success;
                glGetProgramiv(m_id, GL_LINK_STATUS, &success);
                if (!success)
                {
                    char infoLog[512];
                    glGetProgramInfoLog(m_id, 512, NULL, infoLog);
                    std::cout << "[ERROR]: Shader Program Linking Failed\n" << infoLog << "\n";

                    // prevent further use of shader
                    m_init = false;
                }
                else
                {
                    glDeleteShader(m_idFrag);
                    glDeleteShader(m_idVert);
                    m_linked = true;
                }
            }
            else
            {
                std::cout << "[ERROR]: Shader has not been inited\n";
            }
        }

        void Shader::setUniform(const std::string& name, int value, UniformWarningType specification) const
        {
            switch (specification)
            {
            case Shader::UniformWarningType::doNotGiveWarning:
                if (m_linked && m_init)
                    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
                break;
            case Shader::UniformWarningType::giveWarning:
                if (m_linked && m_init)
                {
                    GLuint loc = glGetUniformLocation(m_id, name.c_str());
                    if (loc != 0)
                        glUniform1i(loc, value);
                    else
                        std::cout << "WARNING: Could not find int uniform GLShader::setUniform\n";
                }
                break;
            }
        }

        void Shader::setUniform(const std::string& name, glm::mat4 value, UniformWarningType specification) const
        {
            switch (specification)
            {
            case Shader::UniformWarningType::doNotGiveWarning:
                if (m_linked && m_init)
                    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
                break;
            case Shader::UniformWarningType::giveWarning:
                if (m_linked && m_init)
                {
                    GLuint loc = glGetUniformLocation(m_id, name.c_str());
                    if (loc != 0)
                        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
                    else
                        std::cout << "WARNING: Could not find mat4 uniform GLShader::setUniform\n";
                }
                break;
            }
        }

        void Shader::setUniform(const std::string& name, float value, UniformWarningType specification) const
        {
            switch (specification)
            {
            case Shader::UniformWarningType::doNotGiveWarning:
                if (m_linked && m_init)
                    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
                break;
            case Shader::UniformWarningType::giveWarning:
                if (m_linked && m_init)
                {
                    GLuint loc = glGetUniformLocation(m_id, name.c_str());
                    if (loc != 0)
                        glUniform1f(loc, value);
                    else
                        std::cout << "WARNING: Could not find float uniform GLShader::setUniform\n";
                }
                break;
            }
        }

        void Shader::setUniform(const std::string& name, glm::vec3 value, UniformWarningType specification) const
        {
            switch (specification)
            {
            case Shader::UniformWarningType::doNotGiveWarning:
                if (m_linked && m_init)
                    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
                break;
            case Shader::UniformWarningType::giveWarning:
                if (m_linked && m_init)
                {
                    GLuint loc = glGetUniformLocation(m_id, name.c_str());
                    if (loc != 0)
                        glUniform3f(loc, value.x, value.y, value.z);
                    else
                        std::cout << "WARNING: Could not find float uniform GLShader::setUniform\n";
                }
                break;
            }
        }

        void Shader::use() const
        {
            if (m_linked && m_init)
                glUseProgram(m_id);
        }

        void Shader::reset()
        {
            if (m_init && m_linked)
                glDeleteProgram(m_id);
            m_init = false;
            m_linked = false;
            m_id = 0;
            m_idFrag = 0;
            m_idVert = 0;
        }

        void Shader::unuse() const
        {
            if (m_linked && m_init)
                glad_glUseProgram(0);
        }

        GLuint Shader::getID() const
        {
            if (m_linked && m_init)
                return m_id;

            return 0;
        }
    }
}