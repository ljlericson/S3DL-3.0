#include "CubeMap.h"

namespace Core::OpenGlBackend
{
	CubeMap::CubeMap(const char* texFpath1,
					const char* texFpath2,
					const char* texFpath3,
					const char* texFpath4,
					const char* texFpath5,
					const char* texFpath6)
		: 
		m_verts({
		//   Coordinates
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f}),

		m_inds ({
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3 })
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_verts.size(), m_verts.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_inds.size(), m_inds.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		std::string facesCubemap[6] =
		{
			texFpath1,
			texFpath2,
			texFpath3,
			texFpath4,
			texFpath5,
			texFpath6
		};

		// Creates the cubemap texture object
		glGenTextures(1, &m_tex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_tex);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// These are very important to prevent seams
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		// This might help with seams on some systems
		//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		// Cycles through all the textures and attaches them to the cubemap object
		for (unsigned int i = 0; i < 6; i++)
		{
			int width, height, nrChannels;
			unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				stbi_set_flip_vertically_on_load(false);
				GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
				glTexImage2D
				(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					format,
					width,
					height,
					0,
					format,
					GL_UNSIGNED_BYTE,
					data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
				stbi_image_free(data);
			}
		}
		stbi_set_flip_vertically_on_load(true); // restore for other textures
	}

	void CubeMap::draw(Shader* shad, Camera* cam)
	{
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);


		shad->use();
		cam->matrix(shad, "camMat");
		glUniform1i(glGetUniformLocation(shad->getID(), "skybox"), 0);

		//glm::vec3 camPos = cam->pos;
		//float* f = cam->getOrientation().data();
		//glm::vec3 camFront = glm::vec3(f[0], f[1], f[2]);
		//glm::vec3 camUp = glm::vec3(f[3], f[4], f[5]);

		//// Zero out vertical component
		//camFront.y = 0.0f;
		//camFront = glm::normalize(camFront);

		//// Rebuild view matrix for skybox
		//m_view = glm::mat4(1.0f);
		//m_view = glm::lookAt(glm::vec3(0.0f), camFront, glm::vec3(0.0f, 1.0f, 0.0f));

		m_view = glm::scale(glm::mat4(glm::mat3(cam->getView())), glm::vec3(-1.0f, 1.0f, 1.0f));
		m_projection = glm::perspectiveFov(glm::radians(cam->fov), (float)Util::width, (float)Util::height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shad->getID(), "view"), 1, GL_FALSE, glm::value_ptr(m_view));
		glUniformMatrix4fv(glGetUniformLocation(shad->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(m_vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_tex);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
	}
}