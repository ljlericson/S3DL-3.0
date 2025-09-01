#include "shader.h"

Render::Shader::Shader()
    : m_init(false), m_linked(false), m_id(0), m_idFrag(0), m_idVert(0), m_fragSrc{""}, m_vertSrc{""}
{   }

Render::Shader::Shader(std::string_view fpathVert, std::string_view fpathFrag)
    : m_init(false), m_linked(false), m_id(0), m_idFrag(0), m_idVert(0), m_fragSrc{""}, m_vertSrc{""}
{
    std::ifstream fileVert(fpathVert.data());
    std::ifstream fileFrag(fpathFrag.data());
    
    if(!fileVert || !fileFrag)
    {
        std::cout << "[ERROR]: Invalid file given to shader on init\n";
    }
    else
    {
        std::string lineFrag;
        while (std::getline(fileFrag, lineFrag)) 
            m_fragSrc += lineFrag + "\n";

        std::string lineVert;
        while (std::getline(fileVert, lineVert)) 
            m_fragSrc += lineVert + "\n";
        
        m_init = true; 
    }
    
}


Render::Shader::~Shader()
{
    if (m_init)
        glDeleteProgram(m_id);
}

void Render::Shader::build()
{
    if(m_init)
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
            std::cout << "[ERROR]: Fragment shader compilation failed\n" << infoLog << "\n";
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
    {   std::cout << "[ERROR]: Shader must be initialised before attempting to build\n";  }
}

void Render::Shader::attach()
{
    if(m_init)
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

void Render::Shader::use() const
{
    if(m_linked && m_init)
        glUseProgram(m_id);
}

void Render::Shader::unuse() const
{
    if (m_linked && m_init)
        glad_glUseProgram(0);
}

GLuint Render::Shader::getID() const 
{   
    if (m_linked && m_init)
        return m_id;

	return 0;
}