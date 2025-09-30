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
					fpath,
					aiProcess_ConvertToLeftHanded |
					aiProcess_JoinIdenticalVertices |
					aiProcess_Triangulate |
					aiProcess_FlipUVs |
					aiProcess_PreTransformVertices |
					aiProcess_CalcTangentSpace |
					aiProcess_JoinIdenticalVertices |
					aiProcess_SortByPType
				);

				if(scene)
				{
					auto model = std::make_unique<OpenGlBackend::Model>(textureManager, scene, fpath);

					if (model)
					{
						m_models.insert({
							fpath,
							std::move(model)
							});
						return m_models.at(fpath);
					}
					else { std::print("FATAL ERROR: Model Failed to initialise or link"); return m_models.at(std::string("")); }
				}
				else 
				{
					std::println("[ERROR]: Loading model failed: {}", importer.GetErrorString());
					return m_models.at(std::string(""));
				}
			}
			else
			{
				std::print("INFO: Found existing model...");
				return m_models.at(fpath);
			}
		}

		std::shared_ptr<OpenGlBackend::Model> ModelManager::getModel(const std::string& fpath)
		{
			if (m_models.contains(fpath))
			{
				return m_models.at(fpath);
			}
			else
			{
				std::println("WARNING: No model found for given path (ModelManager::getModel), path{}", fpath);
				assert("NO MDOEL FOUND");
				return nullptr; // TODO: find a safer solution to this that doesn't crash the program
			}
		}


		void ModelManager::clear()
		{
			m_models.clear();
			m_refCounts.clear();
			m_idToString.clear();
		}
	}
}