//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_OBJECT2D_H
#define LIBTEST_OBJECT2D_H

#include "Object.h"
#include "GeometryEssentials.h"
#include "VAO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include <memory>
#include <vector>

namespace enpitsu
{
    class Object2D : public Object
    {
        std::vector<GLfloat > vertices;
        std::vector<GLuint > indices;
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vbo;
        std::unique_ptr<EBO> ebo;
        std::unique_ptr<ShaderProgram> shaderProgram;
    public:
        using Object::Object;

        Object2D(Screen *screen, const std::vector<Vector2> &points,
                 const bool &isStatic = true,
                 const std::vector<unsigned int> &drawOrder = std::vector<unsigned int>(0U));

        virtual void init() override;

        virtual void onDestroy() override;

    protected:
        virtual void draw() override;
    };
}


#endif //LIBTEST_OBJECT2D_H
