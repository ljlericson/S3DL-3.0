#include "Model.h"

Render::Model::Model(const std::string& path) 
{
	Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (nullptr == scene) 
    {
        std::cout << "[ERROR]: Loading model failed: " << importer.GetErrorString() << '\n';
    }
    else
    {

        for (uint32_t i = 0; i < scene->mNumMeshes; i++)
        {
            std::vector<float>  vertData;
            std::vector<GLuint> indiData;

			// get vertices, normals and texture coordinates
            for(uint32_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
            {
                aiVector3D vert = scene->mMeshes[i]->mVertices[j];
                aiVector3D norm = scene->mMeshes[i]->mNormals[j];
                aiVector3D tex(0.0f, 0.0f, 0.0f);
                if(scene->mMeshes[i]->mTextureCoords[0]) // does the mesh contain texture coordinates
                {
                    tex = scene->mMeshes[i]->mTextureCoords[0][j];
                }
                vertData.push_back(vert.x);
                vertData.push_back(vert.y);
                vertData.push_back(vert.z);
                vertData.push_back(norm.x);
                vertData.push_back(norm.y);
                vertData.push_back(norm.z);
                vertData.push_back(tex.x);
                vertData.push_back(tex.y);
			}

			// get indices
            for(uint32_t j = 0; j < scene->mMeshes[i]->mFaces->mNumIndices; j++)
				indiData.push_back(scene->mMeshes[i]->mFaces->mIndices[j]);

			// get texture path
            aiString texturePath{};
            scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

            m_childMeshes.push_back(std::make_unique<Mesh>(vertData, indiData, (GLuint)i, texturePath.C_Str()));
        }
    }
}

void Render::Model::Draw(Shader& shader) 
{
	for(const auto& mesh : m_childMeshes)
		mesh->draw(shader);
}