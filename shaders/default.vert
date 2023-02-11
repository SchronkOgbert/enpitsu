#version 450

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;

out vec4 color;

void main()
{
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
    color = inColor;
}