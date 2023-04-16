#ifndef ENPITSU_OBJECT3D_H
#define ENPITSU_OBJECT3D_H

#include "Object.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/SolidColor.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{

    class Object3D : public Object
    {
    protected:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        std::shared_ptr<ShaderProgram> shaderProgram;
        bool isStatic;
        Vector3 origin;

        std::unique_ptr<glm::mat4> model = std::make_unique<glm::mat4>(1.0f);

    public:
        [[nodiscard]] const std::shared_ptr<ShaderProgram> & getShaderProgram() const;

    public:
        using Object::Object;

        explicit Object3D(
                Screen *screen,
                std::vector<Vector3> *points,
                const Vector3 &origin,
                const Vector3 &size,
                std::shared_ptr<ShaderProgram> &&shader,
                const bool &isStatic = true,
                std::vector<unsigned int> *drawOrder = {0}
        );

    protected:
        void tick(const float &delta) override;

        void draw() override;

        void init() override;
    };

} // enpitsu

#endif //ENPITSU_OBJECT3D_H
