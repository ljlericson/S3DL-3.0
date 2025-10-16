#version 330 core
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D diffuse;
uniform sampler2D emissive;
uniform sampler2D roughness;
uniform sampler2D metallic;

// fixed sun-like directional light (normalized)
const vec3 lightDir = normalize(vec3(-0.3, -0.7, -0.6));
// camera assumed to look from +Z axis (you can change this)
const vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));

void main()
{
    vec3 N = normalize(Normal);
    vec3 L = normalize(-lightDir);  // light direction toward surface
    vec3 V = normalize(viewDir);    // camera direction
    vec3 H = normalize(L + V);      // halfway vector

    vec3 albedo = texture(diffuse, TexCoord).rgb;
    vec3 emissiveColor = texture(emissive, TexCoord).rgb;
    float rough = clamp(texture(roughness, TexCoord).r, 0.04, 1.0);
    float metal = clamp(texture(metallic, TexCoord).r, 0.0, 1.0);

    // Fresnel-Schlick
    vec3 F0 = mix(vec3(0.04), albedo, metal);
    float VoH = max(dot(V, H), 0.0);
    vec3 F = F0 + (1.0 - F0) * pow(1.0 - VoH, 5.0);

    // Normal Distribution (GGX)
    float alpha = rough * rough;
    float NoH = max(dot(N, H), 0.0);
    float alpha2 = alpha * alpha;
    float denom = (NoH * NoH) * (alpha2 - 1.0) + 1.0;
    float D = alpha2 / (3.14159265 * denom * denom);

    // Geometry (Smith Schlick-GGX)
    float NoV = max(dot(N, V), 0.0);
    float NoL = max(dot(N, L), 0.0);
    float k = (alpha + 1.0) * (alpha + 1.0) / 8.0;
    float Gv = NoV / (NoV * (1.0 - k) + k);
    float Gl = NoL / (NoL * (1.0 - k) + k);
    float G = Gv * Gl;

    // Specular term
    vec3 specular = (D * F * G) / (4.0 * max(NoV, 0.001) * max(NoL, 0.001));

    // Diffuse term (Lambert + energy conservation)
    vec3 kd = (1.0 - F) * (1.0 - metal);
    vec3 diffuseTerm = kd * albedo / 3.14159265;

    // Final lighting (direct only, no IBL)
    vec3 color = (diffuseTerm + specular) * NoL + emissiveColor;

    FragColor = vec4(color, 1.0);
}
