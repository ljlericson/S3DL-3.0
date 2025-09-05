#include "camera.h"


Render::Camera::Camera(glm::vec3 pos)
{
    gravity = 2.0f;
    grounded = false;
    jump = false;
    jumpTicks = 0;
    firstClick = false;
    firstJump = false;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    cam_mat = glm::mat4(1.0f);
    this->pos = pos;
    speed = 0.1f;
    sens = 1.0f; 

}

void Render::Camera::update_matrix(float fnear, float ffar)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(pos, pos + orientation, up);
    proj = glm::perspective(glm::radians(fov), (float)(WIDTH / HEIGHT), fnear, ffar);
    cam_mat = proj * view;
}

void Render::Camera::matrix(Shader& shad, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shad.getID(), uniform), 1, GL_FALSE, glm::value_ptr(cam_mat));
}


// not my code!!!!
void Render::Camera::inputs(GLFWwindow* window, float height_data)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
        if(!grounded)
            pos += speed * orientation;
        else
            pos += speed * glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
        pos += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
        if(!grounded)
            pos += speed * -orientation;
        else
            pos += speed * -glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
        pos += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !jump && grounded)
	{
        jump = true;
        firstJump = true;
	}
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed *= 1.6f;
    }
    
    // handles jumping (the one bit of code i made)
    // Handles key inputs
    if(jump && grounded)
    {
        if(pos.y <= height_data && !firstJump)
        {
            pos.y = height_data;
            jump = false;
            jumpTicks = 0;
        }
        else
        {
            pos.y += -0.001f * gravity * jumpTicks + 0.06f;
            jumpTicks ++;
        }
        firstJump = false;
    }
    else if(grounded)
    {
        pos.y = height_data;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sens * 5.0f * (float)(mouseY - (HEIGHT / 2)) / HEIGHT;
		float rotY = sens * 5.0f * (float)(mouseX - (WIDTH / 2)) / WIDTH;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}

std::array<float, 6> Render::Camera::getOrientation()
{
    return {
        orientation.x, orientation.y, orientation.z,
        up.x, up.y, up.z
    };
}