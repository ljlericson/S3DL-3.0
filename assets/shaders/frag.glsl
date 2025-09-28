#version 330 core
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
    // Sample base color
    vec4 baseColor = texture(tex0, TexCoord);

    // Discard transparent pixels
    if (baseColor.a < 0.1)
        discard;

    // --- Dot product lighting ---
    // Hard-coded light direction (normalized)
    vec3 lightDir = normalize(vec3(0.3, 0.7, 0.6));

    // Ensure the normal is normalized
    vec3 N = normalize(Normal);

    // Lambertian diffuse term
    float diff = max(dot(N, lightDir), 0.0);

    // Optional: add a tiny bit of ambient light so nothing is totally black
    float ambient = 0.15;

    // Final lighting multiplier
    float lighting = ambient + diff * (1.0 - ambient);

    FragColor = vec4(baseColor.rgb * lighting, baseColor.a);
}

// #version 330 core
// in vec2 TexCoord;
// in vec3 Normal;

// out vec4 FragColor;

// uniform sampler2D tex0;
// // test
// void main() {
// 	if(texture(tex0, TexCoord).w < 0.1)
// 		discard;
//     FragColor = texture(tex0, TexCoord);
// 	// FragColor = vec4(1.0, 0.5, 0.2, 1.0);
// }