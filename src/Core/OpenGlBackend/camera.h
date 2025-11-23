#pragma once

#include <iostream>
#include <array>
// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
// local
#include "shader.h"
#include "../../Utils/Utils.h"

namespace Core
{
    namespace OpenGlBackend
    {
        class Camera
        {
        private:
            // opengl matrix math
            std::pair<glm::vec3, glm::vec3> m_orientationAndUp;
            glm::mat4 m_camMat;
            glm::mat4 m_view;

        public:
            glm::vec3 pos;
            float fov;

            Camera(glm::vec3 pos);

            void updateMatrix(float fnear, float ffar);

            glm::mat4 getMatrix() const;

            std::pair<glm::vec3, glm::vec3>& getOrientations();

            glm::mat4 getView() const;
        };
    }
}