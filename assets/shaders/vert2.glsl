// #version 430 core

// layout(location = 0) in vec3 aPos;
// layout(location = 1) in vec3 aNormal;
// layout(location = 2) in vec2 aTexCoord;

// layout(std430, binding = 1) buffer InstanceData {
//     mat4 instanceModel[];
// };

// uniform mat4 camMat;

// out vec2 TexCoord;
// out vec3 Normal;
// out vec3 FragPos;

// void main() 
// {
//     mat4 model = (gl_InstanceID < instanceModel.length()) 
//                 ? instanceModel[gl_InstanceID] 
//                 : mat4(1.0);
    
//     gl_Position = camMat * model * vec4(aPos, 1.0);

//     FragPos = vec3(model * vec4(aPos, 1.0));
//     TexCoord = aTexCoord;         // don’t randomly offset by +1
//     Normal = mat3(model) * aNormal;
// }

#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

layout(std430, binding = 1) buffer InstanceData {
    mat4 instanceModel[];
};

uniform mat4 camMat;
uniform mat4 model;
uniform bool useInstance;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    mat4 model = useInstance ? instanceModel[gl_InstanceID] : model; // model uniform for base
    gl_Position = camMat * model * vec4(aPos, 1.0);
    
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}