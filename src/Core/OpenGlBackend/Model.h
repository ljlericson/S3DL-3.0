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

namespace Core
{
	namespace OpenGlBackend
	{
		class Model
		{
		public:
			Model(const std::string& fpath);

			~Model();

			void Draw(Shader& shader, Camera& camera);

			GLuint getNumTextures() const;

			size_t getLocalID() const;

		public:
			std::string m_name;
			glm::vec3 m_pos;
		private:
			static inline size_t sm_numModels = 0;
			size_t m_localID = 0;
			// manages textures
			TextureManager* m_textureManager = nullptr;
			glm::vec3 m_posBefore;
			std::vector<std::unique_ptr<Mesh>> m_childMeshes;
		};
	}
}