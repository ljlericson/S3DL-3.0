#include "Model.h"

namespace Core
{
    namespace OpenGlBackend
    {
        Model::~Model()
        {

        }

        Model::Model(Manager::TextureManager* textureManager, const aiScene* model, const std::string& path)
            : m_pos(0.0f), m_posBefore(0.0f), m_textureManager(textureManager)
        {
            // scene should be valid considering it is controlled by modelManager
            if (model)
            {
                m_name = std::string(model->mName.C_Str());
                if (m_name.empty())
                    m_name = std::filesystem::path(path).stem().string();

                std::filesystem::path modelDir = std::filesystem::path(path).parent_path();
                GLuint numTextures = 0;
                for (uint32_t i = 0; i < model->mNumMeshes; i++)
                {
                    std::vector<float>  vertData;
                    std::vector<GLuint> indiData;

                    for (uint32_t j = 0; j < model->mMeshes[i]->mNumVertices; j++)
                    {
                        aiVector3D vert = model->mMeshes[i]->mVertices[j];
                        aiVector3D norm = model->mMeshes[i]->mNormals[j];
                        aiVector3D tex(0.0f, 0.0f, 0.0f);

                        if (model->mMeshes[i]->HasTextureCoords(0))
                        {

                            tex = model->mMeshes[i]->mTextureCoords[0][j];
                            // Flip Y so OpenGL renders correctly
                            tex.y = 1.0f - tex.y;
                        }

                        vertData.insert(vertData.end(),
                            {
                                vert.x, vert.y, vert.z,
                                norm.x, norm.y, norm.z,
                                tex.x, tex.y
                            });
                    }

                    // indices
                    for (uint32_t j = 0; j < model->mMeshes[i]->mNumFaces; j++)
                    {
                        aiFace face = model->mMeshes[i]->mFaces[j];
                        for (uint32_t k = 0; k < face.mNumIndices; k++)
                            indiData.push_back(face.mIndices[k]);
                    }

                    // material / texture
                    aiString texturePath;
                    auto* mat = model->mMaterials[model->mMeshes[i]->mMaterialIndex];

                    std::shared_ptr<Texture> diffuse = this->loadTexture(mat, model, i, aiTextureType_DIFFUSE, Manager::TextureManager::ReturnOnError::returnInvalidTexture);
                    std::shared_ptr<Texture> metallic = nullptr; // this->loadTexture(mat, model, i, aiTextureType_METALNESS, Manager::TextureManager::ReturnOnError::returnNullptr);
                    std::shared_ptr<Texture> emissive = nullptr; // this->loadTexture(mat, model, i, aiTextureType_EMISSIVE, Manager::TextureManager::ReturnOnError::returnNullptr);
                    std::shared_ptr<Texture> roughness = nullptr; // this->loadTexture(mat, model, i, aiTextureType_DIFFUSE_ROUGHNESS, Manager::TextureManager::ReturnOnError::returnNullptr);

                    if (diffuse != m_textureManager->getInvalidTex<OpenGlBackend::Texture>())
                    {
                        // pass empty string if no texture
                        m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, diffuse, metallic, roughness, emissive));
                        std::cout << "INFO--  Loaded mesh: " << model->mMeshes[i]->mName.C_Str() << '\n'
                            << "------  with a valid diffuse texture\n\n";
                    }
                    else
                    {
                        // pass empty string if no texture
                        m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, m_textureManager->getInvalidTex<OpenGlBackend::Texture>(), metallic, roughness, emissive));
                        std::cout << "INFO--  Loaded mesh: " << model->mMeshes[i]->mName.C_Str() << '\n'
                            << "------  with an invalid texture(no diffuse tex found)\n\n";
                    }
                }

                // this way around for indexing starting at 1 (m_localID of 0 indicates an invalid mesh)
                sm_numModels++;
                m_localID = sm_numModels;
            }
        }

        std::shared_ptr<Texture> Model::loadTexture(aiMaterial* mat, const aiScene* model, size_t meshNum, aiTextureType texType, Manager::TextureManager::ReturnOnError specification)
        {
            std::shared_ptr<Texture> tex = nullptr;
            aiString texturePath;

            if (mat->GetTextureCount(texType) > 0)
            {
                if (mat->GetTexture(texType, 0, &texturePath) == AI_SUCCESS)
                {
                    std::string texStr = texturePath.C_Str();

                    // assume embedded texture because external ends
                    // up being weird and not working
                    const aiTexture* embeddedTex = model->GetEmbeddedTexture(texStr.c_str());
                    std::cout << "INFO--  Loading embedded texture: " << texStr
                        << "\n------  For mesh: " << model->mMeshes[meshNum]->mName.C_Str() << "\n";
                    tex = m_textureManager->newTexture<OpenGlBackend::Texture>(embeddedTex, texStr, specification);
                    std::cout << '\n';
                }
            }
            if (tex)
                return tex;
            else
                return (specification == Manager::TextureManager::ReturnOnError::returnNullptr) ? nullptr : m_textureManager->getInvalidTex<OpenGlBackend::Texture>();
        }

        Model::operator bool()
        {
            return m_localID != 0;
        }

        void Model::Draw(Shader* shader, Camera* camera)
        {
            if(m_localID != 0)
            {
                for (const auto& mesh : m_childMeshes)
                {
                    if (m_pos != m_posBefore)
                        mesh->m_pos += (this->m_pos - this->m_posBefore);

                    mesh->draw(shader, camera);
                }
                m_posBefore = m_pos;
            }
        }

        size_t Model::getLocalID() const
        {
            return m_localID;
        }


        GLuint Model::getNumTextures() const
        {
            return m_textureManager->getNumTextures();
        }
    }
}