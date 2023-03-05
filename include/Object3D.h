//
// Created by weekendUM on 2/18/2023.
//

#ifndef LIBTEST_OBJECT3D_H
#define LIBTEST_OBJECT3D_H

#include "Object.h"
#include "ShaderProgram.h"
#include <vector>

namespace enpitsu
{

    class Object3D : public Object
    {
    protected:
        std::vector<GLfloat > vertices;
        std::vector<GLuint > indices;
        std::unique_ptr<ShaderProgram> shaderProgram;
        bool isStatic;
        Vector3 origin;
        std::shared_ptr<ShaderProgram> shader;
    public:
        [[nodiscard]] const std::unique_ptr<ShaderProgram> &getShaderProgram() const;

    public:
        using Object::Object;
        Object3D(
                Screen* screen,
                const std::vector<Vector3> points,
                const Vector3 &origin,
                const Vector3 &size,
                ShaderProgram* shader,
                const bool &isStatic = true,
                const std::vector<unsigned int> drawOrder = {0}
                );
    };

} // enpitsu

#endif //LIBTEST_OBJECT3D_H
