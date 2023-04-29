#ifndef ENPITSU_EBO_H
#define ENPITSU_EBO_H

#include "enpitsu/helpers/defines.h"

class EBO
{
    GLuint ID;
    GLsizeiptr size;
public:
    EBO(GLuint *indices, const GLsizeiptr &size, const bool &isStatic = true);

    virtual ~EBO();

    void Bind() const;

    void Unbind() const;

    void Delete();

    [[nodiscard]] GLuint getId() const;

    [[nodiscard]] GLsizeiptr getSize() const;

    void setSize(GLsizeiptr size);

    void Update(GLuint* indices) const;
};


#endif //ENPITSU_EBO_H
