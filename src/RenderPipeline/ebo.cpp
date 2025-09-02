#include "ebo.h"

// class EBO

Render::EBO::EBO()
{
    
}

// want to copy
Render::EBO::EBO(std::vector<GLuint> indices, GLsizeiptr size)
{
	// create buffer object
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
	// every bind comes with an unbind
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Render::EBO::~EBO()
{
    glDeleteBuffers(1, &id);
}

void Render::EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void Render::EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

