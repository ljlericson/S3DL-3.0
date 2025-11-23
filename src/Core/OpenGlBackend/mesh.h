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

			void addInstance(glm::mat4 mat);

			void removeInstance(size_t pos);

			glm::mat4& getInstance(size_t pos) const;

			void draw(Shader* shader, Camera* camera) const;

		public:
			glm::vec3 m_pos;
			glm::mat4 m_rot;

		private:
			struct Instance
			{
				// SSBO containing model matrices for THIS mesh's instances
				inline static GLuint s_ssbo = 0;

				Instance(const glm::mat4& mat);
				~Instance() = default;

				static void upload(const std::vector<std::unique_ptr<Instance>>& instances);

				glm::mat4 m_mat;
			};

			GLsizei m_vertexCount, m_indexCount;

			VAO m_vao;
			EBO m_ebo;
			VBO m_vbo;
			std::shared_ptr<Texture> m_diffuse = nullptr;
			std::shared_ptr<Texture> m_metallic = nullptr;
			std::shared_ptr<Texture> m_emissive = nullptr;
			std::shared_ptr<Texture> m_roughness = nullptr;

			// Unique ptr for controlled lifetime
			//std::vector<std::unique_ptr<Instance>> m_instances;
		};
	}
}