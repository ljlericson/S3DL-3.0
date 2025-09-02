#version 410 core

layout (location = 0) in vec3 aPos;       // position
layout (location = 1) in vec3 aNormal;    // normal (unused here)
layout (location = 2) in vec2 aTexCoord;  // texture coordinates

uniform mat4 camMat;   // passed from Camera::matrix()
uniform mat4 model;

out vec2 TexCoord;

void main()
{
    vec3 crnt_pos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = camMat * vec4(crnt_pos, 1.0);
    TexCoord = aTexCoord;
}