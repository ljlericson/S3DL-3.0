#include "mesh.h"

namespace Core
{
    namespace OpenGlBackend
    {
        // vertData layout: [0] pos(3), [1] normal(3), [2] texcoords(2)
        Mesh::Mesh(std::vector<float>& vertData, std::vector<GLuint>& indiData, GLuint texUnit, const char* fpathTex)
            : m_pos(0.0f),
            m_vertexCount(GLsizei(vertData.size()) / 8),
            m_indexCount(GLsizei(indiData.size())),
            m_ebo{ indiData, GLsizeiptr(indiData.size() * sizeof(GLuint)) },
            m_vbo{ vertData.data(), GLsizeiptr(vertData.size() * sizeof(float)) },
            m_diffuse{ std::make_shared<Texture>(fpathTex, texUnit, GL_TEXTURE_2D) }
        {
            m_vao.bind();
            m_ebo.bind();
            m_vao.linkAttrib(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // pos
            m_vao.linkAttrib(m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal
            m_vao.linkAttrib(m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // texcoords
            m_vao.unbind();
            m_ebo.unbind();
        }

        // vertData layout: [0] pos(3), [1] normal(3), [2] texcoords(2)
        Mesh::Mesh(std::vector<float>& vertData,
            std::vector<GLuint>& indiData,
            std::shared_ptr<Texture> diffuse,
            std::shared_ptr<Texture> metallic,
            std::shared_ptr<Texture> emissive,
            std::shared_ptr<Texture> roughness)

            : m_pos(0.0f),
            m_vertexCount(GLsizei(vertData.size()) / 8),
            m_indexCount(GLsizei(indiData.size())),
            m_ebo{ indiData, GLsizeiptr(indiData.size() * sizeof(GLuint)) },
            m_vbo{ vertData.data(), GLsizeiptr(vertData.size() * sizeof(float)) },
            m_diffuse{ diffuse },
            m_emissive{ emissive },
            m_roughness{ roughness },
            m_metallic{ metallic }
        {
            m_vao.bind();
            m_ebo.bind();

            m_vao.linkAttrib(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                       // pos
            m_vao.linkAttrib(m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));     // normal
            m_vao.linkAttrib(m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));     // texcoords
            m_vao.unbind();
            m_ebo.unbind();
        }

        void Mesh::addInstance(glm::mat4 mat)
        {
            //m_instances.push_back(std::make_unique<Instance>(mat));
        }

        void Mesh::removeInstance(size_t pos)
        {
            //m_instances.erase(m_instances.begin() + pos);
        }

        glm::mat4& Mesh::getInstance(size_t pos) const
        {
            //return m_instances[pos]->m_mat;
            return *const_cast<glm::mat4*>(&this->m_rot); // temp for compiler warning sake
        }

        Mesh::Instance::Instance(const glm::mat4& mat)
            : m_mat(mat) {      }

        void Mesh::Instance::upload(const std::vector<std::unique_ptr<Instance>>& instances)
        {
            if (s_ssbo == 0)
                glGenBuffers(1, &s_ssbo);

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_ssbo);

            if (instances.empty())
            {
                glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
            }
            else
            {
                // Write instance matrices contiguously
                glBufferData(GL_SHADER_STORAGE_BUFFER,
                    instances.size() * sizeof(glm::mat4),
                    &instances[0]->m_mat,
                    GL_DYNAMIC_DRAW);
            }

            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, s_ssbo);
        }

        void Mesh::draw(Shader* shader, Camera* camera) const
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_pos);
            model *= m_rot;

            auto& [orientation, up] = camera->getOrientations();

            shader->use();
            shader->setUniform("model", model, Shader::UniformWarningType::giveWarning);
            shader->setUniform("uTime", (float)glfwGetTime(), Shader::UniformWarningType::doNotGiveWarning);
            shader->setUniform("noiseStrength", 0.0f, Shader::UniformWarningType::doNotGiveWarning);
            shader->setUniform("lightPos", camera->pos, Shader::UniformWarningType::doNotGiveWarning);
            shader->setUniform("cameraPos", camera->pos, Shader::UniformWarningType::doNotGiveWarning);
            shader->setUniform("cameraUp", up, Shader::UniformWarningType::doNotGiveWarning);
            shader->setUniform("cameraOrientation", orientation, Shader::UniformWarningType::doNotGiveWarning);
            
            // !! camera matrix !!
            shader->setUniform("camMat", camera->getMatrix(), OpenGlBackend::Shader::UniformWarningType::giveWarning);

            m_vao.bind();
            m_ebo.bind();
            // diffuse is always correct since texture manager
            // gives it an invalid texture if failed to load
            m_diffuse->bind();

            if (m_emissive)
                m_emissive->bind();
            if (m_metallic)
                m_metallic->bind();
            if (m_roughness)
                m_roughness->bind();

            m_diffuse->uniform(shader->getID(), "diffuse");

            if(m_emissive)
                m_emissive->uniform(shader->getID(), "emissive");
            if(m_roughness)
                m_roughness->uniform(shader->getID(), "roughness");
            if(m_metallic)
                m_metallic->uniform(shader->getID(), "metallic");

            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);

            //// instanced meshes
            //if (!m_instances.empty())
            //{
            //    Instance::upload(m_instances);              // SSBO
            //    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Instance::s_ssbo);
            //    shader->setUniform("useInstance", true, Shader::UniformWarningType::giveWarning);

            //    glDrawElementsInstanced(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr,
            //        static_cast<GLsizei>(m_instances.size()));
            //}

            m_diffuse->unbind();

            if (m_emissive)
                m_emissive->unbind();
            if (m_metallic)
                m_metallic->unbind();
            if (m_roughness)
                m_roughness->unbind();

            m_ebo.unbind();
            m_vao.unbind();
            shader->unuse();
            
            if (Util::checkGlErrors())
                std::cout << "MESH::DRAW1: " << Util::getGlErrAfterCheck();

        }
    }
}