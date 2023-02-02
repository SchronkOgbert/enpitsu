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
public:
    VAO();

    void LinkVBO(VBO vbo, const GLuint &layout);

    void Bind();

    void Unbind();

    void Delete();

    GLuint getId() const;
};


#endif //LIBTEST_VAO_H
