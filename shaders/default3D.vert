#version 450

layout (location = 1) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;
layout (location = 4) in vec3 inNormals;

out vec4 color;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;

void main()
{
    float w = distance(vertexPosition, cameraPosition);
    gl_Position = camMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1);
    color = inColor;
}