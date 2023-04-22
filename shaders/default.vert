#version 450

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;

out vec4 color;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = camMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
    color = inColor;
}