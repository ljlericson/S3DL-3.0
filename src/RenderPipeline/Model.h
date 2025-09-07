#pragma once
#include <memory>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "TextureManager.h"

namespace Render
{
	class Model
	{
	public:
		Model(const std::string& fpath);

		void Draw(Shader& shader, Camera& camera);

		GLuint getNumTextures() const;

		size_t getLocalID() const;

		std::string m_name;
	public:
		glm::vec3 m_pos;
	private:
		size_t m_localID = 0;
		static inline size_t sm_numModels = 0;
		TextureManager m_textureManager;
		glm::vec3 m_posBefore;
		std::vector<std::unique_ptr<Mesh>> m_childMeshes;
	};
}