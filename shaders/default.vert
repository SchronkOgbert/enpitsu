#version 450

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 inColor;

out vec4 color;

void main()
{
    color = inColor;
    gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0);
}