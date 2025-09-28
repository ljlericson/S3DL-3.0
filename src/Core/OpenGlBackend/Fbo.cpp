#include "Fbo.h"

namespace Core
{
    namespace OpenGlBackend
    {
        FBO::FBO(Shader* shad)
            : m_id(0), m_fboTextureID(0), m_rbo(0), m_shad(shad)
        {
            float rectVerts[] = {
                // positions   // texCoords
                 1.0f, -1.0f,  1.0f, 0.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                -1.0f,  1.0f,  0.0f, 1.0f,

                 1.0f,  1.0f,  1.0f, 1.0f,
                 1.0f, -1.0f,  1.0f, 0.0f,
                -1.0f,  1.0f,  0.0f, 1.0f
            };

            glGenVertexArrays(1, &m_scrRectVAO);
            glGenBuffers(1, &m_scrRectVBO);
            glBindVertexArray(m_scrRectVAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_scrRectVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rectVerts), rectVerts, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

            glGenFramebuffers(1, &m_id);
            glBindFramebuffer(GL_FRAMEBUFFER, m_id);

            glGenTextures(1, &m_fboTextureID);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_fboTextureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Util::width, Util::height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboTextureID, 0);

            // after attaching color texture
            GLenum bufs[] = { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(1, bufs);

            glGenRenderbuffers(1, &m_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Util::width, Util::height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

            GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cout << "ERROR: Framebuffer failed to init: " << fboStatus << std::endl;
                m_id = 0;
            }
            else
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

        }

        FBO::~FBO()
        {
            if (m_id > 0)
                glDeleteFramebuffers(1, &m_id);
            if (m_rbo > 0)
                glDeleteRenderbuffers(1, &m_rbo);
            if (m_fboTextureID > 0)
                glDeleteTextures(1, &m_fboTextureID);

            delete m_shad;
        }

        void FBO::startPreRender() const
        {
            if (m_id > 0)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, m_id);
                glViewport((GLint)Util::viewportPos.x, (GLint)Util::viewportPos.y, Util::width, Util::height);
                glEnable(GL_DEPTH_TEST);
                glDepthMask(GL_TRUE);                // allow depth writes
                glClearDepth(1.0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
        }

        void FBO::postRender() const
        {
            if (m_id > 0)
            {
                if (Util::checkGlErrors())
                    std::cout << "FBO POST1: " << Util::getGlErrAfterCheck();

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                m_shad->use();
                glDisable(GL_DEPTH_TEST);
                glBindVertexArray(m_scrRectVAO);
                GLint prevActive;
                glGetIntegerv(GL_ACTIVE_TEXTURE, &prevActive);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, m_fboTextureID);
                GLint loc = glGetUniformLocation(m_shad->getID(), "scrTex");
                if (loc == -1 && true) // sometimes disable this error because its annoying
                {
                    std::cerr << "ERROR: FBO texture uniform not found!\n";
                }
                else
                {
                    glUniform1i(loc, 0);
                }
                if (Util::checkGlErrors())
                    std::cout << "FBO POST2: " << Util::getGlErrAfterCheck();
                glDrawArrays(GL_TRIANGLES, 0, 6);
                if (Util::checkGlErrors())
                    std::cout << "FBO POST3: " << Util::getGlErrAfterCheck();
                glActiveTexture(prevActive);
            }
        }

        GLuint FBO::getTexID() const
        {
            return m_fboTextureID;
        }
    }
}