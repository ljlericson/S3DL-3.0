#pragma once
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include "camera.h"

namespace Render
{
	class Mesh
	{
	public:
		Mesh() = default;

		Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex);

		Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, Texture* texture);

		void draw(Shader& shader, Camera& camera) const;

	public:
		glm::vec3 m_pos;

	private:
		GLsizei m_vertexCount, m_indexCount;

		VAO m_vao;
		EBO m_ebo;
		Texture* m_texture = nullptr; // not owned
	};
}