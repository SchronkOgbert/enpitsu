#version 450

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D textureObject;

void main()
{
    FragColor = texture(textureObject, textureCoords);
}