//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_SHADERPROGRAM_H
#define ENPITSU_SHADERPROGRAM_H

#include "defines.h"
#include "Exception.h"

#include <glad/glad.h>
#include <experimental/string>

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

    private:
        static char *readShaderFile(const char *filename);

        void hasCompiled(const GLuint &shader);

        void hasLinked();

    public:
        ShaderProgram(const char *vertexFile, const char *fragmentFile);

        virtual void Create();

        virtual void Delete();

        [[nodiscard]] GLuint getId() const;
    };
}


#endif //ENPITSU_SHADERPROGRAM_H
