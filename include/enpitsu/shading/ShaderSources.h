#ifndef LIBTEST_SHADERSOURCES_H
#define LIBTEST_SHADERSOURCES_H

#include "enpitsu/helpers/defines.h"

namespace enpitsu
{
    static std::unique_ptr<std::map<std::string, const char*>> defaultShaderSources(
            new std::map<std::string, const char*>{
                    {"default.vert", "#version 450\n"
                                     "\n"
                                     "layout (location = 0) in vec3 vertexPosition;\n"
                                     "layout (location = 2) in vec4 inColor;\n"
                                     "\n"
                                     "out vec4 color;\n"
                                     "\n"
                                     "uniform float scaleX = 1;\n"
                                     "uniform float scaleY = 1;\n"
                                     "uniform float scaleZ = 1;\n"
                                     "\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(vertexPosition.x * scaleX, vertexPosition.y * scaleY, vertexPosition.z * scaleZ, 1.0);\n"
                                     "    color = inColor;\n"
                                     "}"},
                    {"default.frag", "#version 450\n"
                                     "\n"
                                     "in vec4 color;\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = color;\n"
                                     "}"},
                    {"texture.vert", "#version 450\n"
                                     "\n"
                                     "layout (location = 0) in vec2 vertexPosition;\n"
                                     "layout (location = 3) in vec2 textureData;\n"
                                     "\n"
                                     "uniform float scale;\n"
                                     "\n"
                                     "out vec2 textureCoords;\n"
                                     "\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(vertexPosition.x * scale, vertexPosition.y * scale, 0.0f * scale, 1.0);\n"
                                     "    textureCoords = textureData;\n"
                                     "}"},
                    {"texture.frag", "#version 450\n"
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
                                          "uniform mat4 camMatrix;\n"
                                          "\n"
                                          "void main()\n"
                                          "{\n"
                                          "    gl_Position = camMatrix * vec4(inPos, 1.0);\n"
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
                    }
            });
}

#endif //LIBTEST_SHADERSOURCES_H
