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

        void init() override;

        std::unique_ptr<glm::mat4> view = std::make_unique<glm::mat4>(1.0f);
        std::unique_ptr<glm::mat4> projection = std::make_unique<glm::mat4>(1.0f);

        void tick(const float &delta) override;
    public:
        Camera3D(Screen* screen, const Vector3 &position, const Vector2 &size);

        virtual void updateMatrix(const float &nearPlane, const float &farPlane, const char *uniformName);

        [[nodiscard]] const Vector3 &getPosition() const;

        void setPosition(const Vector3& position);

        [[nodiscard]] const Vector3 &getOrientation() const;

        void setOrientation(const Vector3& orientation);

        int getFov() const;

        void setFov(int fov);
    };
}


#endif //ENPITSU_CAMERA3D_H
