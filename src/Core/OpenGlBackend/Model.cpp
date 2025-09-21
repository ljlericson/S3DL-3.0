#include "Model.h"

namespace Core
{
    namespace OpenGlBackend
    {
        Model::~Model()
        {
            delete m_textureManager;
        }

        Model::Model(const std::string& path)
            : m_pos(0.0f), m_posBefore(0.0f), m_textureManager(new TextureManager{})
        {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path,
                aiProcess_ConvertToLeftHanded |
                aiProcess_JoinIdenticalVertices |
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
                aiProcess_PreTransformVertices |
                aiProcess_CalcTangentSpace |
                aiProcess_JoinIdenticalVertices |
                aiProcess_SortByPType);

            if (!scene)
            {
                std::cout << "[ERROR]: Loading model failed: " << importer.GetErrorString() << '\n';
                return;
            }

            m_name = std::string(scene->mName.C_Str());
            if (m_name.empty())
                m_name = std::filesystem::path(path).stem().string();

            std::filesystem::path modelDir = std::filesystem::path(path).parent_path();
            GLuint numTextures = 0;
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {
                std::vector<float>  vertData;
                std::vector<GLuint> indiData;

                for (uint32_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
                {
                    aiVector3D vert = scene->mMeshes[i]->mVertices[j];
                    aiVector3D norm = scene->mMeshes[i]->mNormals[j];
                    aiVector3D tex(0.0f, 0.0f, 0.0f);

                    if (scene->mMeshes[i]->HasTextureCoords(0))
                    {

                        tex = scene->mMeshes[i]->mTextureCoords[0][j];
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
                for (uint32_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
                {
                    aiFace face = scene->mMeshes[i]->mFaces[j];
                    for (uint32_t k = 0; k < face.mNumIndices; k++)
                        indiData.push_back(face.mIndices[k]);
                }

                // material / texture
                aiString texturePath;
                Texture* tex = nullptr;
                auto* mat = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

                if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
                {
                    if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
                    {
                        std::string texStr = texturePath.C_Str();

                        if ((!texStr.empty() && texStr[0] == '*') || true)
                        {
                            // Embedded texture
                            const aiTexture* embeddedTex = scene->GetEmbeddedTexture(texStr.c_str());
                            std::cout << "INFO--  Loading embedded texture: " << texStr
                                << "\n------  For mesh: " << scene->mMeshes[i]->mName.C_Str() << "\n";
                            tex = m_textureManager->newTexture(embeddedTex, texStr);
                            std::cout << '\n';
                        }
                        else
                        {
                            // External texture
                            std::filesystem::path fullPath = modelDir / texStr;
                            tex = m_textureManager->newTexture(fullPath.string().c_str(), GL_TEXTURE_2D);
                        }
                    }
                    // pass empty string if no texture
                    m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, tex));
                    std::cout << "INFO--  Loaded mesh: " << scene->mMeshes[i]->mName.C_Str() << '\n'
                        << "------  with a valid diffuse texture\n\n";
                }

                // pass empty string if no texture
                m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, m_textureManager->getInvalidTex()));
                std::cout << "INFO--  Loaded mesh: " << scene->mMeshes[i]->mName.C_Str() << '\n'
                    << "------  with an invalid texture(no diffuse tex found)\n\n";
            }
            // this way around for starting at 0 indexing
            m_localID = sm_numModels;
            sm_numModels++;
        }

        void Model::Draw(Shader& shader, Camera& camera)
        {
            for (const auto& mesh : m_childMeshes)
            {
                if (m_pos != m_posBefore)
                    mesh->m_pos += (this->m_pos - this->m_posBefore);

                mesh->draw(shader, camera);
            }
            m_posBefore = m_pos;
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