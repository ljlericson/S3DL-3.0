// #version 330 core
// in vec3 TexCoords;
// out vec4 FragColor;
// uniform samplerCube skybox;

// void main()
// {
//     FragColor = texture(skybox, normalize(TexCoords));
// }

#version 330 core
in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube skybox;
const float uTime = 0;

// Controls
const float noiseStrength = 0.005;     // noise amplitude
const float noiseScale = 25.0;         // noise frequency
const float pixelation = 1000.0;        // lower = more blocky
const float blurRadius = 2.0;          // 0.5-2.0 range

// Random generator
float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// Simple 2D noise
float noise(vec2 pos) {
    vec2 i = floor(pos);
    vec2 f = fract(pos);
    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main()
{
    // === 1. Convert direction to UV-like coordinates for pixelation ===
    // Project onto a sphere to get 2D coords (latitude-longitude)
    vec2 uv;
    uv.x = atan(TexCoords.z, TexCoords.x) / (2.0 * 3.1415926) + 0.5; // azimuth
    uv.y = asin(TexCoords.y) / 3.1415926 + 0.5;                     // elevation

    // === 2. Pixelation ===
    vec2 pixelatedUV = floor(uv * pixelation) / pixelation;

    // === 3. Blur ===
    vec3 color = vec3(0.0);
    float total = 0.0;

    // Approximate blur by sampling neighboring pixels in UV space
    vec2 texel = vec2(1.0 / pixelation); // approximate texel size in UV space
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            vec2 offset = vec2(x, y) * texel * blurRadius;
            // Convert back to direction for cubemap sampling
            float phi = (pixelatedUV.x + offset.x - 0.5) * 2.0 * 3.1415926;
            float theta = (pixelatedUV.y + offset.y - 0.5) * 3.1415926;

            vec3 dir;
            dir.x = cos(theta) * cos(phi);
            dir.y = sin(theta);
            dir.z = cos(theta) * sin(phi);

            color += texture(skybox, normalize(dir)).rgb;
            total += 1.0;
        }
    }
    vec3 blurredColor = color / total;

    // === 4. Add animated noise ===
    float n = noise(pixelatedUV * noiseScale + vec2(uTime * 10.0, uTime * 5.0));
    vec3 noisyColor = blurredColor + (n - 0.5) * noiseStrength;

    FragColor = vec4(noisyColor, 1.0);
}
