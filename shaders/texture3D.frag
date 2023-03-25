#version 450

out vec4 FragColor;

in vec2 textureCoords; // coordinates

uniform sampler2D textureObject; // data

void main()
{
    FragColor = texture(textureObject, textureCoords);
}