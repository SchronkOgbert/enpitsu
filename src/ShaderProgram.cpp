//
// Created by weekendUM on 1/24/2023.
//

#include "ShaderProgram.h"
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    const auto* vertexData = readShaderFile(vertexFile);
    const auto* fragmentData = readShaderFile(fragmentFile);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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
    std::cout << "compiled shader " << ID << '\n';
}

void ShaderProgram::Delete()
{
    glDeleteProgram(ID);
}

char* ShaderProgram::readShaderFile(const char *filename)
{
    std::ifstream fin(filename);
    fin.seekg(0, std::ios::end);
    const unsigned size = unsigned(fin.tellg()) + 2;
    char* result = new char[size];
    fin.seekg(0, std::ios::beg);
    fin.read(result, size);
    return result;
}
