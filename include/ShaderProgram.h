//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_SHADERPROGRAM_H
#define ENPITSU_SHADERPROGRAM_H

#include "defines.h"

#include <glad/glad.h>
#include <experimental/string>

class ShaderProgram
{
    GLuint ID;

private:
    static char* readShaderFile(const char *filename);
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    virtual void Create();
    virtual void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //ENPITSU_SHADERPROGRAM_H
