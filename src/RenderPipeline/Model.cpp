#include "Model.h"

Render::Model::Model(const std::string& path) 
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene) {
        std::cout << "[ERROR]: Loading model failed: " << importer.GetErrorString() << '\n';
        return;
    }

    std::filesystem::path modelDir = std::filesystem::path(path).parent_path();
	GLuint numTextures = 0;
    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        std::vector<float>  vertData;
        std::vector<GLuint> indiData;

        // vertices
        for (uint32_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++) {
            aiVector3D vert = scene->mMeshes[i]->mVertices[j];
            aiVector3D norm = scene->mMeshes[i]->mNormals[j];
            aiVector3D tex(0.0f, 0.0f, 0.0f);

            if (scene->mMeshes[i]->mTextureCoords[0]) {
                tex = scene->mMeshes[i]->mTextureCoords[0][j];
            }

            vertData.insert(vertData.end(), { vert.x, vert.y, vert.z,
                                              norm.x, norm.y, norm.z,
                                              tex.x, tex.y });
        }

        // indices
        for (uint32_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++) {
            aiFace face = scene->mMeshes[i]->mFaces[j];
            for (uint32_t k = 0; k < face.mNumIndices; k++)
                indiData.push_back(face.mIndices[k]);
        }

        // material / texture
        aiString texturePath;
        Texture tex;
        auto* mat = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

        if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            std::string texStr = texturePath.C_Str();

            if (!texStr.empty() && texStr[0] == '*') {
                // Embedded texture
                int texIndex = atoi(texStr.c_str() + 1);
                aiTexture* embeddedTex = scene->mTextures[texIndex];
                tex = Texture(embeddedTex, numTextures, texStr);
                numTextures++;
            }
            else {
                std::string texStr = texturePath.C_Str();
                if (!texStr.empty() && texStr[0] != '*')
                {
                    // External texture → join with model directory
                    std::filesystem::path fullPath = modelDir / texStr;
                    tex = Texture(fullPath.string().c_str(), numTextures, GL_TEXTURE_2D);
                    numTextures++;
                }
            }
        }

        // pass empty string if no texture
        m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, tex));
    }
}

void Render::Model::Draw(Shader& shader, Camera& camera) 
{
	for(const auto& mesh : m_childMeshes)
		mesh->draw(shader, camera);
}