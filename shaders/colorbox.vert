#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 sharedColor;
uniform float time;

void main() {
   float cosTheta = cos(time);
   float sinTheta = sin(time);

   float x = aPos.x * cosTheta - aPos.y * sinTheta;
   float y = aPos.x * sinTheta + aPos.y * cosTheta;

   // gl_Position = vec4(x, y, 0, 1.0);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   sharedColor = aColor;
}

