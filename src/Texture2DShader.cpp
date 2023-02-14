//
// Created by weekendUM on 2/13/2023.
//

#include "Texture2DShader.h"
#include "Bell/Core.h"

using bell::core::println;

namespace enpitsu
{
    enpitsu::Texture2DShader::Texture2DShader(Texture2D *textureObject) :
            ShaderProgram("shaders/texture.vert", "shaders/texture.frag")
    {
        this->textureObject = std::unique_ptr<Texture2D>(textureObject);
    }

    Texture2DShader::Texture2DShader(const char *vertexFile, const char *fragmentFile, Texture2D *textureObject):
            ShaderProgram(vertexFile, fragmentFile)
    {
        this->textureObject = std::unique_ptr<Texture2D>(textureObject);
    }

    void Texture2DShader::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
                                 const bool &isStatic)
    {
        ShaderProgram::Create(vertices, indices, vertexSize, isStatic);
        textureCoords = std::make_unique<VBO>(&coordData[0],
                                              sizeof(GLfloat) * coordData.size(),
                                              VBO::objectLayout::TEXTURE2D,
                                              isStatic);
        vao->LinkVBO(*textureCoords);
        GLuint textureScale = glGetUniformLocation(ID, "scale");
        glUniform1f(textureScale, 1.0F);
        GLfloat scale;
        glGetUniformfv(ID, glGetUniformLocation(ID, "scale"), &scale);
        println("\nTexture scale:\n", scale);
        glUniform1i(glGetUniformLocation(ID, "textureObject"), 0);
        GLint texObj;
        glGetUniformiv(ID, glGetUniformLocation(ID, "textureObject"), &texObj);
        println("Texture object: ", texObj);
        textureCoords->Unbind();
    }

    void Texture2DShader::Bind()
    {
        ShaderProgram::Bind();
        textureObject->Bind();
    }
} // enpitsu