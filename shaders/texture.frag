#version 450

out vec4 FragColor;

in vec2 textureCoordinates;

uniform sampler2D textureObject;

void main()
{
    FragColor = texture(textureObject, textureCoordinates);
}