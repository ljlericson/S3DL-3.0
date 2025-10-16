#pragma once
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../BasicBackend/mesh.h"

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include "camera.h"

namespace Core
{
	namespace OpenGlBackend
	{
		class Mesh : public BasicBackend::BasicMesh
		{
		public:
			Mesh() = default;

			Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex);

			Mesh(std::vector<float>& vertData, 
				 std::vector<GLuint>& indiData, 
				 std::shared_ptr<Texture> diffuse,
				 std::shared_ptr<Texture> metallic,
				 std::shared_ptr<Texture> emissive,
				 std::shared_ptr<Texture> roughness);

			~Mesh() override;

			void draw(Shader* shader, Camera* camera) const;

		public:
			glm::vec3 m_pos;

		private:
			struct Instance
			{
				Instance(glm::mat4 translation);
				glm::mat4 mat;
			};

			GLsizei m_vertexCount, m_indexCount;

			VAO m_vao;
			EBO m_ebo;
			VBO m_vbo;
			std::shared_ptr<Texture> m_diffuse = nullptr;
			std::shared_ptr<Texture> m_metallic = nullptr;
			std::shared_ptr<Texture> m_emissive = nullptr;
			std::shared_ptr<Texture> m_roughness = nullptr;

			// instances
			std::vector<std::unique_ptr<Instance>> m_instances;
		};
	}
}