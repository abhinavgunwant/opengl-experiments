#version 330 core

out vec4 FragColor;
in vec3 sharedColor;

uniform float opacity;

void main() {
    float r = sharedColor.x * opacity;
    float g = sharedColor.y * opacity;
    float b = sharedColor.z * opacity;

    FragColor = vec4(r, g, b, 1);
}

