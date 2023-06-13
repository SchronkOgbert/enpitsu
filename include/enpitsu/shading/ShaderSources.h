#ifndef ENPITSU_SHADERSOURCES_H
#define ENPITSU_SHADERSOURCES_H

#include "enpitsu/helpers/defines.h"

namespace enpitsu
{

    std::map<unsigned int, std::string> GLErrors
            {
                    {GL_NO_ERROR, "GL_NO_ERROR"},
                    {GL_INVALID_VALUE, "GL_INVALID_VALUE "},
                    {GL_INVALID_OPERATION, "GL_INVALID_OPERATION "},
                    {GL_INVALID_ENUM, "GL_INVALID_ENUM "}
            };

    static std::unique_ptr<std::map<std::string, std::string>> defaultShaderSources(
            new std::map<std::string, std::string>{
                    {"default.vert",   "#version 450\n"
                                       "\n"
                                       "layout (location = 0) in vec3 vertexPosition;\n"
                                       "layout (location = 2) in vec4 inColor;\n"
                                       "\n"
                                       "out vec4 color;\n"
                                       "\n"
                                       "uniform mat4 camMatrix;\n"
                                       "uniform mat4 modelMatrix;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = camMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);\n"
                                       "    color = inColor;\n"
                                       "}"},
                    {"default.frag",   "#version 450\n"
                                       "\n"
                                       "in vec4 color;\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = color;\n"
                                       "}"},
                    {"texture.vert",   "#version 450\n"
                                       "\n"
                                       "layout (location = 0) in vec2 vertexPosition;\n"
                                       "layout (location = 3) in vec2 textureData;\n"
                                       "\n"
                                       "uniform mat4 camMatrix;\n"
                                       "uniform mat4 modelMatrix;\n"
                                       "\n"
                                       "out vec2 textureCoords;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = camMatrix * modelMatrix * vec4(vertexPosition.x, vertexPosition.y, 1, 1.0);\n"
                                       "    textureCoords = textureData;\n"
                                       "}"},
                    {"texture.frag",   "#version 450\n"
                                       "\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "in vec2 textureCoords;\n"
                                       "\n"
                                       "uniform sampler2D textureObject;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = texture(textureObject, textureCoords);\n"
                                       "}"},
                    {
                     "texture3D.vert", "#version 450\n"
                                       "\n"
                                       "layout (location = 0) in vec3 inPos;\n"
                                       "\n"
                                       "layout (location = 3) in vec2 inTex;\n"
                                       "\n"
                                       "out vec4 outCol;\n"
                                       "\n"
                                       "out vec2 textureCoords;\n"
                                       "\n"
                                       "uniform mat4 cam3DMatrix;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = cam3DMatrix * vec4(inPos, 1.0);\n"
                                       "    textureCoords = inTex;\n"
                                       "}"
                    },
                    {
                     "texture3D.frag", "#version 450\n"
                                       "\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "in vec2 textureCoords; // coordinates\n"
                                       "\n"
                                       "uniform sampler2D textureObject; // data\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = texture(textureObject, textureCoords);\n"
                                       "}"
                    },
                    {
                     "default3D.vert", "#version 450\n"
                                       "\n"
                                       "layout (location = 1) in vec3 vertexPosition;\n"
                                       "layout (location = 2) in vec4 inColor;\n"
                                       "layout (location = 4) in vec3 inNormal;\n"
                                       "\n"
                                       "out vec4 color;\n"
                                       "out vec3 normal;\n"
                                       "out vec3 position;\n"
                                       "\n"
                                       "uniform mat4 cam3DMatrix;\n"
                                       "uniform mat4 modelMatrix;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    vec4 positionBuffer = modelMatrix * vec4(vertexPosition, 1);\n"
                                       "    mat3 normalMatrix = mat3(modelMatrix);\n"
                                       "    normalMatrix = inverse(normalMatrix);\n"
                                       "    gl_Position = cam3DMatrix * modelMatrix * vec4(vertexPosition, 1);\n"
                                       "    color = inColor;\n"
                                       "    normal = normalize(inNormal * normalMatrix);\n"
                                       "    position = vec3(positionBuffer);\n"
                                       "}"
                    },
                    {
                     "default3D.frag", "#version 450\n"
                                       "\n"
                                       "in vec4 color;\n"
                                       "in vec3 normal;\n"
                                       "in vec3 position;\n"
                                       "\n"
                                       "uniform vec4 lightColor = vec4(1, 1, 1, 1);\n"
                                       "uniform vec3 lightPos;\n"
                                       "uniform vec3 cameraPosition;\n"
                                       "uniform float ambient = 0.05f;\n"
                                       "uniform float diffuse = 0.0f;\n"
                                       "uniform float specular = 0.3f;\n"
                                       "uniform float radius = 8.0f;\n"
                                       "\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    vec3 normalizedNormal = normalize(normal);\n"
                                       "    vec3 lightDirection = normalize(lightPos - position);\n"
                                       "    float diffuseVal = max(dot(normalizedNormal, lightDirection), diffuse);\n"
                                       "    vec4 colorCompose = color * lightColor;\n"
                                       "    float distanceBasedIntensity = min(radius / distance(lightPos, position), 1.0f);\n"
                                       "    FragColor = vec4(vec3(colorCompose) * (ambient + diffuseVal) * distanceBasedIntensity, colorCompose.w * color.w);\n"
                                       "}"
                    },
                    {
                     "light.vert",     "#version 450\n"
                                       "\n"
                                       "layout (location = 1) in vec3 vertexPosition;\n"
                                       "\n"
                                       "uniform mat4 modelMatrix;\n"
                                       "uniform mat4 cam3DMatrix;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = cam3DMatrix * modelMatrix * vec4(vertexPosition, 1);\n"
                                       "}"
                    },
                    {
                     "light.frag",     "#version 450\n"
                                       "\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "uniform vec4 lightColor = vec4(1, 1, 1, 1);\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = lightColor;\n"
                                       "}"
                    }
            });
}

#endif //ENPITSU_SHADERSOURCES_H
