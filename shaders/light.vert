#version 450

layout (location = 1) in vec3 vertexPosition;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * model * vec4(vertexPosition, 1);
}