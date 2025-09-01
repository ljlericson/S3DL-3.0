#pragma once
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

namespace Render
{
	class Mesh
	{
	public:
		Mesh() = default;

		Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex);

		~Mesh();

		void draw(Shader& shader) const;
	private:
		GLsizei m_vertexCount, m_indexCount;

		glm::vec3 m_pos;
		VAO m_vao;
		EBO m_ebo;
		std::unique_ptr<Texture> m_texture;
	};
}