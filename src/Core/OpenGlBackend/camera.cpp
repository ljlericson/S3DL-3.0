#include "camera.h"

namespace Core
{
    namespace OpenGlBackend
    {
        // TODO: COMPLETELY REFACTOR CLASS
        Camera::Camera(glm::vec3 pos)
            :
            fov(90.0f),
            pos(pos),

            m_view(1.0f),
            m_camMat(1.0f),
            m_orientationAndUp({glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)})
        {   }

        void Camera::updateMatrix(float fnear, float ffar)
        {
            // --- Validate inputs ---
            if (fnear <= 0.001f) fnear = 0.001f;
            if (ffar <= fnear + 0.001f) ffar = fnear + 1000.0f;

            float w = (float)Util::width;
            float h = (float)Util::height;

            if (w <= 0) w = 1;
            if (h <= 0) h = 1;

            float vfov = glm::clamp(fov, 1.0f, 179.0f);

            glm::vec3 forward = m_orientationAndUp.first;
            glm::vec3 up = m_orientationAndUp.second;

            if (glm::length(forward) < 0.0001f)
                forward = glm::vec3(0.0f, 0.0f, -1.0f);

            if (glm::length(up) < 0.0001f)
                up = glm::vec3(0.0f, 1.0f, 0.0f);

            forward = glm::normalize(forward);
            up = glm::normalize(up);

            if (glm::abs(glm::dot(forward, up)) > 0.9999f)
                up = glm::normalize(glm::cross(glm::cross(forward, glm::vec3(1, 0, 0)), forward));

            m_view = glm::lookAt(pos, pos + forward, up);

            float aspect = w / h;
            glm::mat4 proj = glm::perspective(glm::radians(vfov), aspect, fnear, ffar);

            m_camMat = proj * m_view;
        }

        glm::mat4 Camera::getMatrix() const
        {
            return m_camMat;
        }

        std::pair<glm::vec3, glm::vec3>& Camera::getOrientations()
        {
            return m_orientationAndUp;
        }

        glm::mat4 Camera::getView() const
        {
            return m_view;
        }
    }
}