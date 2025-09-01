#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif

namespace Render
{
    class EBO
    {
    public:
        GLuint id;

        EBO();
        EBO(GLuint* indices, GLsizeiptr size);
		~EBO();

        void bind() const;
        void unbind() const;
    };
};
