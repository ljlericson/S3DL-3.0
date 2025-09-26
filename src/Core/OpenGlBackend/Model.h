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
#include "../AssetManagers/TextureManager.h"
#include "../AssetManagers/AssetManager.h"


namespace Core
{
	namespace OpenGlBackend
	{
		class Model
		{
		public:
			Model(Manager::AssetManager* assetManager, const std::string& fpath);

			~Model();

			void Draw(Shader* shader, Camera* camera);

			GLuint getNumTextures() const;

			size_t getLocalID() const;

		public:
			std::string m_name;
			glm::vec3 m_pos;
		private:
			static inline size_t sm_numModels = 0;
			size_t m_localID = 0;
			// manages textures
			glm::vec3 m_posBefore;
			std::vector<std::unique_ptr<Mesh>> m_childMeshes;
			// member reference pointer
			Manager::TextureManager* m_textureManager; // NOT OWNED
		};
	}
}