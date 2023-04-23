#version 450

layout (location = 1) in vec3 vertexPosition;
layout (location = 2) in vec4 inColor;
layout (location = 4) in vec3 inNormal;

out vec4 color;
out vec3 normal;
out vec3 position;

uniform mat4 cam3DMatrix;
uniform mat4 modelMatrix;

void main()
{
    vec4 positionBuffer = modelMatrix * vec4(vertexPosition, 1);
    gl_Position = cam3DMatrix * modelMatrix * vec4(vertexPosition, 1);
    color = inColor;
    normal = inNormal;
    position = vec3(positionBuffer);
}