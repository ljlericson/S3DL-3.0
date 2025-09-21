#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif

namespace Core
{
    namespace OpenGlBackend
    {
        class VBO
        {
        public:
            GLuint id;

            VBO() = default;
            VBO(GLfloat* vertices, GLsizeiptr size);
            ~VBO();

            void bind() const;
            void unbind() const;
        };
    }
}