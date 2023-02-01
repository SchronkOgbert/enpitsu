//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_VBO_H
#define LIBTEST_VBO_H

#include "glad/glad.h"

class VBO
{
    GLuint ID;
public:
    explicit VBO(GLfloat *vertices, const GLsizeiptr &size, const bool &isStatic = true);

    void Bind() const;
    void Unbind();
    void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //LIBTEST_VBO_H
