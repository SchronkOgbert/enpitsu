#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include "cstring"
#include "Bell/Core.h"

using bell::core::println;

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    const auto* vertexData = readShaderFile(vertexFile);
    const auto* fragmentData = readShaderFile(fragmentFile);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    ID = glCreateProgram();
    std::cout << "compiling shader " << ID << "(" << vertexFile << ")\n";

    glShaderSource(vertexShader, 1, &vertexData, nullptr);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentData, nullptr);
    glCompileShader(fragmentShader);

    delete[] vertexData;
    delete[] fragmentData;

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void ShaderProgram::Create()
{
    glUseProgram(ID);
    println("compiled shader ", ID);
}

void ShaderProgram::Delete()
{
    glDeleteProgram(ID);
}

char* ShaderProgram::readShaderFile(const char *filename)
{
    // TODO: replace this with something that runs in a reasonable amount of time
    std::ifstream fin(filename);
    std::string buffer;
    std::string lineBuffer;
    while(std::getline(fin, lineBuffer))
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
