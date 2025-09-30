// #version 330 core
// in vec2 TexCoord;
// in vec3 Normal;

// out vec4 FragColor;

// uniform sampler2D tex0;

// void main()
// {
//     // Sample base color
//     vec4 baseColor = texture(tex0, TexCoord);

//     // Discard transparent pixels
//     if (baseColor.a < 0.1)
//         discard;

//     // --- Dot product lighting ---
//     // Hard-coded light direction (normalized)
//     vec3 lightDir = normalize(vec3(0.3, 0.7, 0.6));

//     // Ensure the normal is normalized
//     vec3 N = normalize(Normal);

//     // Lambertian diffuse term
//     float diff = max(dot(N, lightDir), 0.0);

//     // Optional: add a tiny bit of ambient light so nothing is totally black
//     float ambient = 0.7;

//     // Final lighting multiplier
//     float lighting = ambient + diff * (1.0 - ambient);

//     FragColor = vec4(baseColor.rgb * lighting, baseColor.a);
// }

#version 330 core
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex0;
uniform float uTime;              // Time in seconds from CPU

// Controls
const float noiseStrength = 0.0f;
const float noiseScale = 50.0f;
const float pixelation = 250.0f;  
const float blurRadius = 2.0f;

float rand(vec2 co) 
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float noise(vec2 pos) 
{
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
    // === 1. Pixelation step ===
    // Snap UVs to a coarse grid to simulate low resolution
    vec2 pixelatedUV = floor(TexCoord * pixelation) / pixelation;

    // === 2. Blur step ===
    // Sample a small kernel around the pixelated UV
    vec2 texel = 1.0 / vec2(textureSize(tex0, 0));
    vec3 color = vec3(0.0);
    float total = 0.0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            vec2 offset = vec2(x, y) * texel * blurRadius;
            color += texture(tex0, pixelatedUV + offset).rgb;
            total += 1.0;
        }
    }
    vec3 blurredColor = color / total;

    // === 3. Add animated noise ===
    float n = noise(pixelatedUV * noiseScale + vec2(uTime * 10.0, uTime * 5.0));
    vec3 noisyColor = blurredColor + (n - 0.5) * noiseStrength;

    FragColor = vec4(noisyColor, 1.0);
}
