#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    vec4 sampled = vec4(1, 1, 1, texture(text, TexCoords).r);
    // vec4 sampled = vec4(texture(text, TexCoords), 1.0);
    color = vec4(textColor, 1) * sampled;
    // color = vec4(1, 1, 1, 1) * sampled;
    // FragColor = color;
}

