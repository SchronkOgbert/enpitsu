#include "enpitsu/shading/Texture2DShader.h"

namespace enpitsu
{
    enpitsu::Texture2DShader::Texture2DShader(Texture2D *textureObject) :
            ShaderProgram("texture.vert", "texture.frag")
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
        PLOGD << "Vertices " << coordData;
        glUniform1i(glGetUniformLocation(ID, "textureObject"), 0);
        GLint texObj;
        glGetUniformiv(ID, glGetUniformLocation(ID, "textureObject"), &texObj);
        textureCoords->Unbind();
    }

    void Texture2DShader::Bind()
    {
        ShaderProgram::Bind();
        textureObject->Bind();
    }

    Texture2DShader::~Texture2DShader()
    {
        textureCoords->Delete();
    }
} // enpitsu