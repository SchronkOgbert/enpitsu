#include "enpitsu/objects/Camera2D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/Object2D.h"
#include "enpitsu/objects/Screen.h"

namespace enpitsu
{
    Camera2D::Camera2D(Screen *screen, const Vector2 &position, const Vector2 &size) :
            ControlObject(screen), position(position), size(size),
            projection(glm::scale(glm::ortho(-(this->getOffsetFromCenter()),
                                             this->getOffsetFromCenter(),
                                             -1.0f,
                                             1.0f,
                                             0.0f, 1000000.0f), Vector3(Vector2(1.0f / 8), 1)))
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

    float Camera2D::getUnitScale() const
    {
        return unitScale;
    }

    void Camera2D::setUnitScale(float unitScale)
    {
        this->unitScale = unitScale;
    }

    void Camera2D::screenSizeChanged(const Vector2 &newSize)
    {
        PLOGD << screen->getSize().y << ' ' << screen->getSize().x;
        PLOGD << getOffsetFromCenter();
        projection = glm::scale(glm::ortho(-(this->getOffsetFromCenter()),
                                           this->getOffsetFromCenter(),
                                           -1.0f,
                                           1.0f,
                                           0.0f, 1000000.0f), Vector3(Vector2(1.0f / unitScale), 1));
        updateMatrix();
    }

    float Camera2D::getOffsetFromCenter() const
    {
        return this->screen->getSize().x / this->screen->getSize().y;
    }
} // enpitsu