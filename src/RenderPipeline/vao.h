#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include "vbo.h"

namespace Render
{
    class VAO
    {
    public:
        GLuint id;

        VAO();
        ~VAO();

        void linkAttrib(VBO& vbo, GLuint layout, GLuint numComp, GLenum type, GLsizei stride, void* offset);
        void bind() const;
        void unbind() const;
        void reset();
    };

};