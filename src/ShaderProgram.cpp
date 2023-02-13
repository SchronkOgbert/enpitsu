#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include "cstring"
#include "Bell/Core.h"

using bell::core::println;

namespace enpitsu
{

    ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
    {
        const auto *vertexData = readShaderFile(vertexFile);
        const auto *fragmentData = readShaderFile(fragmentFile);

        if (strlen(vertexData) == 0)
        {
            throw BadShaderSource("Vertex shader source could not be loaded. Is the file path correct");
        }
        if (strlen(fragmentData) == 0)
        {
            throw BadShaderSource("Fragment shader source could not be loaded. Is the file path correct?");
        }

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        ID = glCreateProgram();
        std::cout << "compiling shader " << ID << "(" << vertexFile << ")\n";

        glShaderSource(vertexShader, 1, &vertexData, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentData, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);

        delete[] vertexData;
        delete[] fragmentData;
    }

    void ShaderProgram::Create(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices,
                               const int &vertexSize,
                               const bool &isStatic)
    {
        setVao(new VAO(vertexSize));
        getVao()->Bind();
        setVertexPosition(new VBO(&vertices[0U], sizeof(&vertices[0]) * vertices.size(),
                                  vertexSize == 2 ? VBO::objectLayout::VERTEX2D : VBO::objectLayout::VERTEX3D,
                                  isStatic));
        setEbo(new EBO(&indices[0U], sizeof(&indices[0]) * indices.size(), isStatic));
        glLinkProgram(ID);
        hasCompiled(vertexShader);
        hasCompiled(fragmentShader);
        hasLinked();
        glUseProgram(ID);
    }

    void ShaderProgram::Delete()
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(ID);
    }

    char *ShaderProgram::readShaderFile(const char *filename)
    {
        // TODO: replace this with something that runs in a reasonable amount of time
        std::ifstream fin(filename);
        std::string buffer;
        std::string lineBuffer;
        while (std::getline(fin, lineBuffer))
        {
            buffer += lineBuffer + "\n";
        }
        char *result = new char[buffer.size() + 1];
        strcpy(result, buffer.c_str());
//    println("Read data from file:\n", result);
        return result;
    }

    GLuint ShaderProgram::getId() const
    {
        return ID;
    }

    void ShaderProgram::hasCompiled(const GLuint &shader)
    {
        int compiled;
        glGetShaderiv(ID, GL_COMPILE_STATUS, &compiled);
        char shaderSource[1024];
        glGetShaderSource(shader, 1024, nullptr, shaderSource);
//        println("Shader source:\n------------------\n", shaderSource, "\n-----------------");
        if (!compiled)
        {
            char shaderInfo[1024];
            glGetShaderInfoLog(ID, 1024, nullptr, shaderInfo);
            throw BadShaderCompile(shaderInfo);
        }
    }

    void ShaderProgram::hasLinked()
    {
        int linked;
        glGetProgramiv(ID, GL_LINK_STATUS, &linked);
        if (!linked)
        {
            char programInfo[1024];
            glGetProgramInfoLog(ID, 1024, nullptr, programInfo);
            throw BadShaderLink(programInfo);
        }
    }
}