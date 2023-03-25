//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_EBO_H
#define LIBTEST_EBO_H

#include "helpers/defines.h"

class EBO
{
    GLuint ID;
public:
    EBO(GLuint *indices, const GLsizeiptr &size, const bool &isStatic = true);

    void Bind();

    void Unbind();

    void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //LIBTEST_EBO_H
