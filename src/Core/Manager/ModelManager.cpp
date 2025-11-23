#include "ModelManager.h"
#include "../OpenGlBackend/Model.h"

namespace Core
{
	namespace Manager
	{
		std::shared_ptr<OpenGlBackend::Model> ModelManager::newModelOrGetModel(TextureManager* textureManager, const std::string& fpath)
		{
			if (!m_models.contains(fpath))
			{
				Assimp::Importer importer;
				const aiScene* scene = importer.ReadFile(
					"assets/no_model.fbx",
					//aiProcess_ConvertToLeftHanded | // somehow flips the model
					aiProcess_JoinIdenticalVertices |
					aiProcess_Triangulate |
					aiProcess_PreTransformVertices |
					aiProcess_CalcTangentSpace |
					aiProcess_SortByPType |
					aiProcess_FlipUVs
				);

				if(scene)
				{
					auto model = std::make_shared<OpenGlBackend::Model>(textureManager, scene, fpath);

					if (model)
					{
						m_models.insert({
							fpath,
							std::move(model)
							});
						m_loadThread = new std::thread{ &Core::Manager::ModelManager::loadSceneThread, this, textureManager, fpath };
						return m_models.at(fpath);
					}
					else { std::cout << "FATAL ERROR: Model Failed to initialise or link\n"; return m_models.at(std::string("")); }
				}
				else 
				{
					std::cout << "[ERROR]: Loading model failed: " << importer.GetErrorString() << '\n';
					return m_models.at(std::string(""));
				}
			}
			else
			{
				std::cout << "INFO: Found existing model...\n";
				return m_models.at(fpath);
			}
		}

		size_t ModelManager::newInstance(const std::string& fpath, glm::mat4 model)
		{
			return m_models.at(fpath)->makeInstace(model);
		}

		glm::mat4& ModelManager::getInstanceModel(const std::string& fpath, size_t instaceId)
		{
			return m_models.at(fpath)->getInstanceModel(instaceId);
		}

		std::shared_ptr<OpenGlBackend::Model> ModelManager::getModel(const std::string& fpath)
		{
			if (m_models.contains(fpath))
			{
				return m_models.at(fpath);
			}
			else
			{
				std::cout << "WARNING: No model found for given path (ModelManager::getModel), path: " << fpath << '\n';
				assert("NO MDOEL FOUND");
				return nullptr; // TODO: find a safer solution to this that doesn't crash the program
			}
		}
		 
		void ModelManager::loop()
		{
			switch (m_loadState)
			{
			case LoadState::loading:
				break;
			case LoadState::nothingToLoad:
				break;
			case LoadState::loaded:
				m_loadState = LoadState::nothingToLoad;
				if(m_loadThread->joinable())
					m_loadThread->join();
				
				this->loadModel(std::get<0>(*m_newMeshData), std::get<1>(*m_newMeshData), std::get<2>(*m_newMeshData));

				delete m_loadThread;
				delete m_newMeshData;
				delete m_importer;
			}
		}

		void ModelManager::clear()
		{
			m_models.clear();
		}

		void ModelManager::loadModel(TextureManager* texManager, const aiScene* scene, const std::string& fpath)
		{
			if (scene)
			{
				auto& model = m_models.at(fpath);
				{
					std::scoped_lock lock(m_modelMutex); // lock map before checking
					*model = OpenGlBackend::Model(texManager, scene, fpath);
					if (!*model)
					{
						std::cout << "Model failed to load!\n";
					}
				}
			}
		}

		void ModelManager::loadSceneThread(TextureManager* texManager, const std::string& fpath)
		{
			if (m_models.contains(fpath))
			{
				m_loadState = LoadState::loading;

				m_importer = new Assimp::Importer{};
				const aiScene* scene = m_importer->ReadFile(
					fpath,
					//aiProcess_ConvertToLeftHanded | // somehow flips the model
					aiProcess_JoinIdenticalVertices |
					aiProcess_Triangulate |
					aiProcess_PreTransformVertices |
					aiProcess_CalcTangentSpace |
					aiProcess_SortByPType |
					aiProcess_FlipUVs
				);

				{
					std::scoped_lock lock(m_modelMutex); 
					m_newMeshData = new std::tuple<TextureManager*, const aiScene*, std::string>
					{
						texManager,
						scene,
						fpath
					};
				}

				m_loadState = LoadState::loaded;

				while(m_loadState != LoadState::nothingToLoad)
				{
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(50ms);
				}
			}
		}

	}
}
