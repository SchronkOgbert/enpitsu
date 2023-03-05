//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_VBO_H
#define LIBTEST_VBO_H

#include "defines.h"

class VBO
{
public:
    GLuint ID;
    enum class objectLayout : int
    {
        VERTEX2D = 0,
        VERTEX3D = 1,
        RGBA = 2,
        TEXTURE2D = 3
    };
private:
    objectLayout layout;
public:
    [[nodiscard]] objectLayout getLayout() const
    {
        return layout;
    }

    explicit VBO(GLfloat *vertices, const GLsizeiptr &size, const VBO::objectLayout &layout,
                 const bool &isStatic = true);

    void Bind() const;

    void Unbind();

    void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //LIBTEST_VBO_H
