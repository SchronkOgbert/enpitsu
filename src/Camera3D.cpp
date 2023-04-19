#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Object3D.h"

enpitsu::Camera3D::Camera3D(enpitsu::Screen *screen, const Vector3 &position, const Vector2 &size) :
        ControlObject(screen)
{
    this->size = size;
    this->position = position;
}

void
enpitsu::Camera3D::updateMatrix(const float &nearPlane, const float &farPlane, const char *uniformName)
{
    Vector3 center = position + orientation;
    *view = glm::lookAt(position, center, up);

    *projection = glm::perspective(glm::radians(static_cast<float>(FOV)),
                                   static_cast<float>(size.x) / size.y, nearPlane, farPlane);
    screen->setCamMatrix(glm::value_ptr(*projection * *view));
}

void enpitsu::Camera3D::tick(const float &delta)
{
    if(update)
    {
        updateMatrix(0.01f, 100, "camMatrix");
        update = false;
    }
}

const enpitsu::Vector3 &enpitsu::Camera3D::getPosition() const
{
    return position;
}

void enpitsu::Camera3D::setPosition(const enpitsu::Vector3 &position)
{
    this->position = position;
    update = true;
}

void enpitsu::Camera3D::init()
{
    Object::init();
    updateMatrix(0.1f, 100.0f, "camMatrix");
}

const enpitsu::Vector3 &enpitsu::Camera3D::getOrientation() const
{
    return this->orientation;
}

void enpitsu::Camera3D::setOrientation(const enpitsu::Vector3 &orientation)
{
    this->orientation = orientation;
    update = true;
}

int enpitsu::Camera3D::getFov() const
{
    return FOV;
}

void enpitsu::Camera3D::setFov(int fov)
{
    FOV = fov;
}
