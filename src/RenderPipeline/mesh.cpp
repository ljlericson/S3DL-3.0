#include "mesh.h"

Render::Mesh::~Mesh()
{
    delete m_texture;
}

// vertData layout: [0] pos(3), [1] normal(3), [2] texcoords(2)
Render::Mesh::Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex)
    : m_pos         ( 0.0f ), 
      m_vertexCount ( GLsizei(vertData.size()) / 8 ),
	  m_indexCount  ( GLsizei(indiData.size()) ),
      m_ebo         { indiData, GLsizeiptr(indiData.size() * sizeof(GLuint)) }, 
      m_texture     { new Texture(fpathTex, texUnit, GL_TEXTURE_2D) }
{
    m_vao.bind();
    VBO vbo{ vertData.data(), GLsizeiptr(vertData.size() * sizeof(float)) };
    m_ebo.bind();

    m_vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // pos
    m_vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal
    m_vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // texcoords
    m_vao.unbind();
    m_ebo.unbind();
}

// vertData layout: [0] pos(3), [1] normal(3), [2] texcoords(2)
Render::Mesh::Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, Texture* texture)
    : m_pos(0.0f),
    m_vertexCount(GLsizei(vertData.size()) / 8),
    m_indexCount(GLsizei(indiData.size())),
    m_ebo{ indiData, GLsizeiptr(indiData.size() * sizeof(GLuint)) },
    m_texture{ texture }
{
    m_vao.bind();
    VBO vbo{ vertData.data(), GLsizeiptr(vertData.size() * sizeof(float)) };
    m_ebo.bind();

    m_vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // pos
    m_vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal
    m_vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // texcoords
    m_vao.unbind();
    m_ebo.unbind();
}

void Render::Mesh::draw(Shader& shader, Camera& camera) const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_pos);

 //   shader.use();
	//shader.setUniform("model", model);
 //   m_texture->bind();
 //   // Draw mesh
 //   m_texture->uniform(shader.getID(), "tex0");
	//camera.matrix(shader, "camMat");
 //   m_vao.bind();
 //   glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	//m_texture->unbind();
 //   m_vao.unbind();
 //   shader.unuse();
    shader.use();

    m_texture->uniform(shader.getID(), "tex0");

    shader.setUniform("model", model);
    camera.matrix(shader, "camMat");

    m_vao.bind();
    m_texture->bind();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    m_vao.unbind();

    m_texture->unbind();
    shader.unuse();
}