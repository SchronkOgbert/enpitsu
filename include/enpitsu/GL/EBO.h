#ifndef ENPITSU_EBO_H
#define ENPITSU_EBO_H

#include "enpitsu/helpers/defines.h"

class EBO
{
    GLuint ID;
public:
    EBO(GLuint *indices, const GLsizeiptr &size, const bool &isStatic = true);

    void Bind() const;

    void Unbind() const;

    void Delete();

    [[nodiscard]] GLuint getId() const;
};


#endif //ENPITSU_EBO_H
