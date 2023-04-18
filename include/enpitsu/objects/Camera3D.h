#ifndef ENPITSU_CAMERA3D_H
#define ENPITSU_CAMERA3D_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "ControlObject.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{
    class Camera3D : public ControlObject, public InputEvents
    {
        unsigned moving{0};
    protected:
        Vector2 size;
        Vector3 position;
        Vector3 orientation{0, 0, -1};
        Vector3 up{0, 1, 0};
        float speed{0.1f};
        int FOV{80};

        int speedLeft{0};
        int speedForward{0};
        float mouseSensitivity{0.5f};
        bool justClicked{false};
        Vector2 prevMousePos;
        Vector2 currMousePos;
        float yaw{-90.0f};
        float pitch = 0;
    public:
        const Vector3 &getPosition() const;

        void setPosition(const Vector3 &position);

    protected:

        std::unique_ptr<glm::mat4> view = std::make_unique<glm::mat4>(1.0f);
        std::unique_ptr<glm::mat4> projection = std::make_unique<glm::mat4>(1.0f);

        void tick(const float &delta) override;
    public:
        Camera3D(Screen* screen, const Vector3 &position, const Vector2 &size);

        virtual void updateMatrix(const float &nearPlane, const float &farPlane, const char *uniformName);

        void OnMousePressed(const MouseEvent &event) override;

        void OnMouseReleased(const MouseEvent &event) override;

        void OnKeyPressed(const KeyEvent &event) override;

        void OnKeyReleased(const KeyEvent &event) override;

        void move();
    };
}


#endif //ENPITSU_CAMERA3D_H
