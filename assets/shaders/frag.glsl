// Fragment Shader
#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex0;

void main() {
	if(texture(tex0, TexCoord).w < 0.1)
		discard;
    FragColor = texture(tex0, TexCoord);
	// FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}