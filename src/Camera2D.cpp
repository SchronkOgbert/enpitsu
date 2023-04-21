#include "enpitsu/objects/Camera2D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/Object2D.h"
#include "enpitsu/objects/Screen.h"

namespace enpitsu
{
    const glm::mat4 Camera2D::projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);

    Camera2D::Camera2D(Screen *screen, const Vector2 &position, const Vector2 &size) :
    ControlObject(screen), position(position), size(size)
    {
        view = glm::translate(view, Vector3(position, 16));
    }

    void Camera2D::init()
    {
        Object::init();
        updateMatrix();
    }

    void Camera2D::updateMatrix()
    {
        auto vec3Pos = Vector3(position, 16);
        auto center = vec3Pos + orientation;
        view = glm::lookAt(vec3Pos, center, up);
        screen->setCam2DMatrix(glm::value_ptr(projection * view));
    }
} // enpitsu