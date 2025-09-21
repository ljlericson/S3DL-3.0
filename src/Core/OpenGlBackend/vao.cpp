#include "vao.h"

// class VAO
namespace Core
{
    namespace OpenGlBackend
    {
        VAO::VAO()
        {
            glGenVertexArrays(1, &id);
        }

        VAO::~VAO()
        {
            glDeleteVertexArrays(1, &id);
        }

        void VAO::linkAttrib(VBO& vbo, GLuint layout, GLuint numComp, GLenum type, GLsizei stride, void* offset)
        {
            vbo.bind();
            glVertexAttribPointer(layout, numComp, type, GL_FALSE, stride, offset);
            glEnableVertexAttribArray(layout);
            vbo.unbind();
        }

        void VAO::bind() const
        {
            glBindVertexArray(id);
        }

        void VAO::unbind() const
        {
            glBindVertexArray(0);
        }

        void VAO::reset()
        {
            glDeleteVertexArrays(1, &id);
            id = 0;
            glGenVertexArrays(1, &id);
        }
    }
}