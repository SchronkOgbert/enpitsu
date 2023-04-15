#version 450

layout (location = 1) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;
layout (location = 4) in vec3 inNormals;

out vec4 color;

uniform float scaleX = 1;
uniform float scaleY = 1;
uniform float scaleZ = 1;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(vertexPosition.x * scaleX, vertexPosition.y * scaleY, vertexPosition.z * scaleZ, 1.0);
    color = inColor;
}