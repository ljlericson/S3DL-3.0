#version 430 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;   // pass in world pos from vertex shader if available

out vec4 FragColor;

uniform sampler2D diffuse;
uniform float uTime;              // Time in seconds from CPU
uniform float noiseStrength;      // e.g. 0.04

// Controls
float time = uTime / 10.0;
const float pixelation = 250.0;   // lower = more pixelated
const float wobbleStrength = 0.002; // e.g. 0.002

// Random & noise helpers
float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float noise(vec2 pos) {
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) +
           (c - a) * u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}


// Lighting
vec3 lightDir = normalize(vec3(0.3, 0.7, 0.6));

void main()
{
    // === 1. Pixelated UVs ===
    vec2 pixelatedUV = floor(TexCoord * pixelation) / pixelation;

    // === 2. Affine "wobble" effect ===
    // Approximate PS1 lack of perspective correction by nudging UVs
    float wobble = sin(time + FragPos.z * 5.0) * wobbleStrength;
    pixelatedUV += vec2(wobble, -wobble);

    // === 3. Sample texture (blocky look) ===
    vec3 texColor = texture(diffuse, pixelatedUV).rgb;

    // === 4. Simple Lambert lighting ===
    vec3 N = normalize(Normal);
    float diff = max(dot(N, lightDir), 0.0);
    float ambient = 0.2;
    float lighting = ambient + diff * (1.0 - ambient);

    // === 5. Output ===
    FragColor = vec4(texColor * lighting, 1.0);
}

// #version 330 core

// in vec2 TexCoord;
// in vec3 Normal;
// in vec3 FragPos; 

// out vec4 FragColor;

// uniform sampler2D diffuse;
// uniform sampler2D emissive;
// uniform sampler2D roughness;
// uniform sampler2D metallic;

// uniform float uTime;              // Time in seconds from CPU
// uniform float noiseStrength;      // e.g. 0.04

// // New uniforms:
// uniform vec3 lightPos;           // world-space light position
// uniform vec3 cameraPos;          // world-space camera position
// uniform vec3 cameraUp;           // camera up vector
// uniform vec3 cameraOrientation;  // camera forward/look vector

// // Stylization controls
// const float noiseScale = 25.0f;
// const float pixelation = 100.0f;  
// const float blurRadius = 0.0f;

// // ---------- Noise helpers ----------
// float rand(vec2 co) {
//     return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
// }

// float noise(vec2 pos) {
//     vec2 i = floor(pos);
//     vec2 f = fract(pos);
//     float a = rand(i);
//     float b = rand(i + vec2(1.0, 0.0));
//     float c = rand(i + vec2(0.0, 1.0));
//     float d = rand(i + vec2(1.0, 1.0));
//     vec2 u = f * f * (3.0 - 2.0 * f);
//     return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
// }

// void main()
// {
//     // === 1. Base material properties ===
//     vec3 albedo = pow(texture(diffuse, TexCoord).rgb, vec3(2.2)); // gamma → linear
//     vec3 emissiveColor = texture(emissive, TexCoord).rgb;
//     float rough = clamp(texture(roughness, TexCoord).r, 0.04, 1.0);
//     float metal = clamp(texture(metallic, TexCoord).r, 0.0, 1.0);

//     // === 2. Lighting vectors ===
//     vec3 N = normalize(Normal);
//     vec3 L = normalize(lightPos - FragPos);     
//     vec3 V = normalize(cameraPos - FragPos);     
//     vec3 H = normalize(L + V);                   

//     // Optional: build view basis from camera vectors (if needed later)
//     vec3 right = normalize(cross(cameraUp, cameraOrientation));
//     vec3 up    = normalize(cross(cameraOrientation, right));

//     // === 3. Light attenuation (inverse-square falloff) ===
//     float distance = length(lightPos - FragPos);
//     // float attenuation = 1.0 / (distance * distance);  // physically based falloff
//     // attenuation = clamp(attenuation * 200.0, 0.0, 1.0);

//     // === 4. BRDF calculations ===
//     vec3 F0 = mix(vec3(0.04), albedo, metal);
//     float NoH = max(dot(N, H), 0.0);
//     float NoV = max(dot(N, V), 0.0);
//     float NoL = max(dot(N, L), 0.0);
//     float VoH = max(dot(V, H), 0.0);

//     // Fresnel (Schlick)
//     vec3 F = F0 + (1.0 - F0) * pow(1.0 - VoH, 5.0);

//     // Normal Distribution (GGX/Trowbridge-Reitz)
//     float alpha = rough * rough;
//     float alpha2 = alpha * alpha;
//     float denom = (NoH * NoH) * (alpha2 - 1.0) + 1.0;
//     float D = alpha2 / (3.14159265 * denom * denom);

//     // Geometry (Smith Schlick-GGX)
//     float k = (alpha + 1.0) * (alpha + 1.0) / 8.0;
//     float Gv = NoV / (NoV * (1.0 - k) + k);
//     float Gl = NoL / (NoL * (1.0 - k) + k);
//     float G = Gv * Gl;

//     // Specular term
//     vec3 specular = (D * F * G) / (4.0 * max(NoV, 0.001) * max(NoL, 0.001));

//     // Diffuse term (Lambert, energy-conserving)
//     vec3 kd = (1.0 - F) * (1.0 - metal);
//     vec3 diffuseTerm = kd * albedo / 3.14159265;

//     // === 5. Final physically-based color ===
//     vec3 lighting = (diffuseTerm + specular) * NoL /* * attenuation*/ + emissiveColor;

//     // === 6. Stylization pass (pixelation + blur + noise) ===
//     vec2 pixelatedUV = floor(TexCoord * pixelation) / pixelation;
//     vec2 texel = 1.0 / vec2(textureSize(diffuse, 0));
//     vec3 stylized = vec3(0.0);
//     float total = 0.0;

//     for (int x = -1; x <= 1; x++) {
//         for (int y = -1; y <= 1; y++) {
//             vec2 offset = vec2(x, y) * texel * blurRadius;
//             stylized += lighting * texture(diffuse, pixelatedUV + offset).rgb;
//             total += 1.0;
//         }
//     }

//     stylized /= total;

//     float n = noise(pixelatedUV * noiseScale + vec2(uTime * 10.0, uTime * 5.0));
//     stylized += (n - 0.5) * noiseStrength;

//     // === 7. Output ===
//     // Apply gamma correction back to sRGB
//     vec3 finalColor = pow(stylized, vec3(1.0 / 2.2));

//     FragColor = vec4(finalColor, 1.0);
// }