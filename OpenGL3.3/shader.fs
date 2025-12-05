#version 330 core
out vec4 FragColor;
in vec3 OurColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.15) * vec4(OurColor, 1.0);
}