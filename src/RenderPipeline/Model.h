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

namespace Render
{
	class Model
	{
	public:
		Model(const std::string& fpath);
		void Draw(Shader& shader, Camera& camera);
		
	private:
		std::vector<std::unique_ptr<Mesh>> m_childMeshes;
	};
}