//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_VAO_H
#define LIBTEST_VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
    GLuint ID;
    GLint vertexSize;
public:
    explicit VAO(const GLint &vertexSize);

    void LinkVBO(VBO vbo);

    void Bind();

    void Unbind();

    void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //LIBTEST_VAO_H
