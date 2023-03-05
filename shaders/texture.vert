#version 450

layout (location = 0) in vec2 vertexPosition;
layout (location = 3) in vec2 textureData;

uniform float scale;

out vec2 textureCoords;

void main()
{
    gl_Position = vec4(vertexPosition.x * scale, vertexPosition.y * scale, 0.0f * scale, 1.0);
    textureCoords = textureData;
}