#version 450

layout (location = 1) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 cam3DMatrix;

void main()
{
    gl_Position = cam3DMatrix * modelMatrix * vec4(vertexPosition, 1);
}