#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif

namespace Render
{
    class VBO
    {
    public:
        GLuint id;

        VBO(GLfloat* vertices, GLsizeiptr size);
        ~VBO();

        void bind() const;
        void unbind() const;
    };
};