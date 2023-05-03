#version 450

in vec4 color;
in vec3 normal;
in vec3 position;

uniform vec4 lightColor = vec4(1, 1, 1, 1);
uniform vec3 lightPos;
uniform vec3 cameraPosition;
uniform float ambient = 0.05f;
uniform float diffuse = 0.0f;
uniform float specular = 0.3f;
uniform float radius = 8.0f;

out vec4 FragColor;
void main()
{
    vec3 normalizedNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPos - position);
    float diffuseVal = max(dot(normalizedNormal, lightDirection), diffuse);
    vec4 colorCompose = color * lightColor;
    float distanceBasedIntensity = min(radius / distance(lightPos, position), 1.0f);
    FragColor = vec4(vec3(colorCompose) * (ambient + diffuseVal) * distanceBasedIntensity, colorCompose.w * color.w);
}