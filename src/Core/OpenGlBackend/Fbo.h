#pragma once
#include <iostream>
#include <glad/glad.h>

#include "../../Utils/Utils.h"
#include "shader.h"
#include "vao.h"

namespace Core
{
	namespace OpenGlBackend
	{
		class FBO
		{
		public:
			FBO(Shader* shad);
			~FBO();

			void startPreRender() const;
			void postRender() const;

			GLuint getTexID() const;

		private:
			GLuint m_id;
			GLuint m_rbo;
			GLuint m_fboTextureID;
			GLuint m_scrRectVAO;
			GLuint m_scrRectVBO;
			Shader* m_shad = nullptr;
		};
	}
}