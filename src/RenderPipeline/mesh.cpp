#include "mesh.h"

Render::Mesh::~Mesh()
{

}

// vertData layout: [0] pos(3), [1] normal(3), [2] texcoords(2)
Render::Mesh::Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex)
    : m_pos         ( 0.0f ), 
      m_vertexCount ( GLsizei(vertData.size()) ),
	  m_indexCount  ( GLsizei(indiData.size()) ),
      m_ebo         { indiData.data(), GLsizeiptr(indiData.size() * sizeof(GLuint)) }, 
      m_texture     { std::make_unique<Texture>(fpathTex, texUnit, GL_TEXTURE_2D) }
{
    m_vao.bind();
    VBO vbo{ vertData.data(), GLsizeiptr(vertData.size() * sizeof(float)) };

    m_vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // pos
    m_vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal
    m_vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // texcoords
    m_vao.unbind();
}

void Render::Mesh::draw(Shader& shader) const
{
    m_texture->bind();
    // Draw mesh
    m_texture->uniform(shader.getID(), "tex0");
    m_vao.bind();
    m_ebo.bind();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	m_texture->unbind();
	m_ebo.unbind();
    m_vao.unbind();
}