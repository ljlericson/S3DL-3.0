#pragma once
#include <iostream>
// external libs
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <stb_image.h>

namespace Render
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
        ~Texture();

        void setParam(GLuint pname, GLuint params);

        void bind() const;

        void uniform(GLuint shadProgram, const char* uName) const;

		void unbind() const;

        void _freeTexBuffer();
    };
};