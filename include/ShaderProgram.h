//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_SHADERPROGRAM_H
#define ENPITSU_SHADERPROGRAM_H

#include "defines.h"
#include "Exception.h"
#include "VAO.h"
#include "EBO.h"

#include <glad/glad.h>
#include <memory>
#include <vector>

namespace enpitsu
{
    class BadShaderCompile : public Exception
    {
    public:
        explicit BadShaderCompile(const char *msg) :
                Exception(msg)
        {}
    };

    class BadShaderLink : public Exception
    {
    public:
        explicit BadShaderLink(const char *msg) :
                Exception(msg)
        {}
    };

    class BadShaderSource : public Exception
    {
    public:
        explicit BadShaderSource(const char *msg) :
                Exception(msg)
        {}
    };

    class ShaderProgram
    {
    protected:
        GLuint ID;
        GLuint vertexShader;
        GLuint fragmentShader;

        //shader data
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vertexPosition;
        std::unique_ptr<EBO> ebo;
    public:
        [[nodiscard]] const std::unique_ptr<VAO> &getVao() const
        {
            return vao;
        }

        [[nodiscard]] const std::unique_ptr<VBO> &getVertexPosition() const
        {
            return vertexPosition;
        }

        [[nodiscard]] const std::unique_ptr<EBO> &getEbo() const
        {
            return ebo;
        }

        void setVao(VAO* vao)
        {
            this->vao = std::unique_ptr<VAO>(vao);
        }

        void setVertexPosition(VBO* vertexPosition)
        {
            this->vertexPosition = std::unique_ptr<VBO>(vertexPosition);
        }

        void setEbo(EBO* ebo)
        {
            ShaderProgram::ebo = std::unique_ptr<EBO>(ebo);
        }

    private:
        static char *readShaderFile(const char *filename);

        void hasCompiled(const GLuint &shader);

        void hasLinked();

    public:
        ShaderProgram(const char *vertexFile, const char *fragmentFile);

        virtual void
        Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const int &vertexSize,
               const bool &isStatic);

        virtual void Delete();

        [[nodiscard]] GLuint getId() const;
    };
}


#endif //ENPITSU_SHADERPROGRAM_H
