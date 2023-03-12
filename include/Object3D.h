//
// Created by weekendUM on 2/18/2023.
//

#ifndef LIBTEST_OBJECT3D_H
#define LIBTEST_OBJECT3D_H

#include "Object.h"
#include "defines.h"
#include "SolidColor.h"

namespace enpitsu
{

    class Object3D : public Object
    {
    protected:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        std::unique_ptr<ShaderProgram> shaderProgram;
        bool isStatic;
        Vector3 origin;
        std::shared_ptr<ShaderProgram> shader;
    public:
        [[nodiscard]] const std::unique_ptr<ShaderProgram> &getShaderProgram() const;

    public:
        using Object::Object;

        explicit Object3D(
                Screen *screen,
                std::vector<Vector3> *points,
                const Vector3 &origin,
                const Vector3 &size,
                ShaderProgram *shader,
                const bool &isStatic = true,
                std::vector<unsigned int> *drawOrder = {0}
        );

    protected:
        void tick(const float &delta) override;

        void draw() override;
    };

} // enpitsu

#endif //LIBTEST_OBJECT3D_H
