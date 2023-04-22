#ifndef ENPITSU_CAMERA3D_H
#define ENPITSU_CAMERA3D_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "ControlObject.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{
    class Camera3D : public ControlObject
    {
        // control
        bool update{false};
    protected:
        Vector2 size;
        Vector3 position;
        Vector3 orientation{0, 0, -1};
        Vector3 up{0, 1, 0};
        int FOV{80};
        bool orthogonal{false};
    protected:

        void init() override;

        glm::mat4 view{1.0f};
        glm::mat4 projection{1.0f};

        void tick(const float &delta) override;
    public:
        Camera3D(Screen* screen, const Vector3 &position, const Vector2 &size);

        virtual void updateMatrix(const float &nearPlane, const float &farPlane);

        [[nodiscard]] const Vector3 &getPosition() const;

        void setPosition(const Vector3& position);

        [[nodiscard]] const Vector3 &getOrientation() const;

        void setOrientation(const Vector3& orientation);

        int getFov() const;

        void setFov(int fov);

        bool isOrthogonal() const;

        void setOrthogonal(bool orthogonal);

        float getOffsetFromCenter() const;
    };
}


#endif //ENPITSU_CAMERA3D_H
