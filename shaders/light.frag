#version 450

out vec4 FragColor;

uniform vec4 lightColor = vec4(1, 1, 1, 1);

void main()
{
    FragColor = lightColor;
}