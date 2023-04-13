#ifndef ENPITSU_VBO_H
#define ENPITSU_VBO_H

#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{
    class ShaderProgram;
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
        unsigned int size;
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

        void Update(GLfloat *newVertices);

        void UpdateScale(const enpitsu::Vector3 &newScale, ShaderProgram *shader);

        [[nodiscard]] GLuint getId() const;
    };
}

#endif //ENPITSU_VBO_H
