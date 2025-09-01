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

#define WIDTH 1280
#define HEIGHT 720

namespace Render
{
    class Camera
    {
    private:
        // jump variables
        bool jump;
        int jumpTicks;
        bool firstJump;
        float yOriginal;
        // mouse input
        bool firstClick;
        // opengl matrix math
        glm::vec3 up;
        glm::vec3 orientation;
        glm::mat4 cam_mat;

    public:
        // use mutable values
        glm::vec3 pos;
        bool grounded;
        float speed;
        float sens;
        float fov;
        float gravity;
        
        
        Camera(glm::vec3 pos);

        void update_matrix(float fnear, float ffar);

        void matrix(Shader& shader, const char* uniform);

        std::array<float, 6> getOrientation();

        void inputs(GLFWwindow* window, float heightData);
    };
}