#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 camMat;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    // vec4 pos = camMat * vec4(aPos, 1.0);
    
    gl_Position = pos.xyww; // depth trick for skybox
}