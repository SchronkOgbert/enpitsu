#ifndef ENPITSU_OBJECT3D_H
#define ENPITSU_OBJECT3D_H

#include "Object.h"

#include "enpitsu/helpers/Drawable.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/shading/SolidColor.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{
    class Object3D : public Object, public Drawable
    {
    protected:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        std::shared_ptr<ShaderProgram> shaderProgram;
        bool isStatic;
        Vector3 origin;
        const Vector3 worldOriginOffset;

        /**
         * in degrees
         */
        Vector3 rotation{};
        Vector3 scale{1, 1, 1};

        bool updateModel{false};

        glm::mat4 model{1};

        void tick(const float &delta) override;

        void draw() override;

        void init() override;

    public:

        using Object::Object;

        [[nodiscard]] const std::shared_ptr<ShaderProgram> & getShaderProgram() const;

        explicit Object3D(
                Screen *screen,
                std::vector<Vector3> *points,
                const Vector3 &origin,
                const Vector3 &size,
                const std::shared_ptr<ShaderProgram> &shader,
                const bool &isStatic = true,
                std::vector<unsigned int> *drawOrder = {0}
        );

        void setLocation(const Vector3& newLocation);

        void setRotation(const Vector3& newRotation);

        void setScale(const Vector3& newScale);

        [[nodiscard]] const Vector3 &getOrigin() const;

        void setOrigin(const Vector3 &origin);

        void forceSetLocation(const Vector3& newLocation);

        void forceSetRotation(const Vector3& newRotation);

        void forceSetScale(const Vector3& newScale);
    };

} // enpitsu

#endif //ENPITSU_OBJECT3D_H
