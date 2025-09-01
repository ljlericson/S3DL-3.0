#include "vao.h"

// class VAO

Render::VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

Render::VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}

void Render::VAO::linkAttrib(VBO& vbo, GLuint layout, GLuint numComp, GLenum type, GLsizei stride, void* offset)
{
    vbo.bind();
    glVertexAttribPointer(layout, numComp, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void Render::VAO::bind() const
{
    glBindVertexArray(id);
}

void Render::VAO::unbind() const 
{
    glBindVertexArray(0);
}

void Render::VAO::reset()
{
    glDeleteVertexArrays(1, &id);
    id = 0;
    glGenVertexArrays(1, &id);
}