#pragma once
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <tuple>
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

			// Either makes/asigins a new model or retrieves an existing model.
			// Uses async loading
			std::shared_ptr<OpenGlBackend::Model> newModelOrGetModel(TextureManager* textureManager, const std::string& fpath);

			std::shared_ptr<OpenGlBackend::Model> getModel(const std::string& fpath);

			void loop();

			void clear();

		private:
			void loadSceneThread(TextureManager* texManager, const std::string& fpath);
			void loadModel(TextureManager* texManager, const aiScene* scene, const std::string& fpath);

		private:
			enum class LoadState 
			{
				loading,
				nothingToLoad,
				loaded
			};

		private:
			// async loading
			std::atomic<LoadState> m_loadState = LoadState::nothingToLoad;
			std::tuple<TextureManager*, const aiScene*, std::string>* m_newMeshData = nullptr;
			Assimp::Importer* m_importer = nullptr;
			std::thread* m_loadThread = nullptr;
			std::mutex m_modelMutex;

			std::unordered_map<std::string, std::shared_ptr<OpenGlBackend::Model>> m_models;

		};
	}
}