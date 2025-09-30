#pragma once
#include <print>
#include <memory>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TextureManager.h"
#include "../OpenGlBackend/Model.h"


namespace Core::OpenGlBackend 
{
	class Model;
}

namespace Core
{
	namespace Manager
	{
		class ModelManager
		{
		public:
			ModelManager() = default;

			// Either makes/asigins a new model or retrieves an existing model
			std::shared_ptr<OpenGlBackend::Model> newModelOrGetModel(TextureManager* textureManager, const std::string& fpath);
			std::shared_ptr<OpenGlBackend::Model> getModel(const std::string& fpath);

			void clear();

		private:
			std::unordered_map<std::string, std::shared_ptr<OpenGlBackend::Model>> m_models;
			std::unordered_map<size_t, std::string> m_idToString;
			std::unordered_map<std::string, size_t> m_refCounts;
		};
	}
}