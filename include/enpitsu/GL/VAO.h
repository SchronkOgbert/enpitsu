#ifndef ENPITSU_VAO_H
#define ENPITSU_VAO_H

#include "enpitsu/helpers/defines.h"
#include "VBO.h"

namespace enpitsu
{
    class VAO
    {
        GLuint ID;
        GLint vertexSize;
    public:
        explicit VAO(const GLint &vertexSize);

        void LinkVBO(VBO vbo);

        void Bind() const;

        void Unbind() const;

        void Delete();

        [[nodiscard]] GLuint getId() const;
    };
}


#endif //ENPITSU_VAO_H
