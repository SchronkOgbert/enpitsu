#version 450

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;

out vec4 color;

uniform float scaleX = 1;
uniform float scaleY = 1;
uniform float scaleZ = 1;

void main()
{
    gl_Position = vec4(vertexPosition.x * scaleX, vertexPosition.y * scaleY, vertexPosition.z * scaleZ, 1.0);
    color = inColor;
}