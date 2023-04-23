#version 450

in vec4 color;
in vec3 normal;
in vec3 position;

out vec4 FragColor;
void main()
{
    FragColor = color;
}