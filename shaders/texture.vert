#version 450

layout (location = 0) in vec2 vertexPosition;
layout (location = 3) in vec2 textureData;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

out vec2 textureCoords;

void main()
{
    gl_Position = camMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, 1, 1.0);
    textureCoords = textureData;
}