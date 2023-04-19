#version 450

out vec4 outColor;

uniform vec4 lightColor = vec4(1, 1, 1, 1);

void main()
{
    outColor = lightColor;
}