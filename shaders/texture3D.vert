#version 450

layout (location = 0) in vec3 inPos;

layout (location = 3) in vec2 inTex;

out vec4 outCol;

out vec2 textureCoords;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(inPos, 1.0);
    textureCoords = inTex;
}