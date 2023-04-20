#version 450

layout (location = 1) in vec3 inPos;
layout (location = 3) in vec2 inTex;
layout (location = 4) in vec3 inNormal;

out vec4 outCol;
out vec2 textureCoords;
out vec3 normal;
out vec3 currPos;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = camMatrix * vec4(inPos, 1.0);
    textureCoords = inTex;
}