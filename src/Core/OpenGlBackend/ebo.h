#pragma once
#include <vector>
#include <glad/glad.h>

namespace Core
{
    namespace OpenGlBackend
    {
        class EBO
        {
        public:
            GLuint id;

            EBO();
            EBO(std::vector<GLuint> indices, GLsizeiptr size);
            ~EBO();

            void bind() const;
            void unbind() const;
        };
    }
}