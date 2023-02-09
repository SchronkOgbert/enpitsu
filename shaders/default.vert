#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 inColor;

out vec4 color;

void main()
{
    color = inColor;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}