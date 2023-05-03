#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Object3D.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/transform.hpp"

enpitsu::Camera3D::Camera3D(enpitsu::Screen *screen, const Vector3 &position, const Vector2 &size) :
        ControlObject(screen)
{
    this->size = size;
    this->position = position;
}

void
enpitsu::Camera3D::updateMatrix(const float &nearPlane, const float &farPlane)
{
    Vector3 center = position + orientation;
    view = glm::lookAt(position, center, up);

    if (orthogonal)
    {
        // TODO fix this abomination if i have the time
        float distance = glm::distance(position, orientation);
        PLOGD << "Distance: " << distance;
        projection = glm::ortho(-(this->getOffsetFromCenter()) * distance,
                                this->getOffsetFromCenter() * distance,
                                -distance,
                                distance,
                                -100000.0f, 10000.0f);
    }
    else
    {
        projection = glm::perspective(glm::radians(static_cast<float>(FOV)),
                                      static_cast<float>(size.x) / size.y, nearPlane, farPlane);
    }
    screen->setCam3DMatrix(glm::value_ptr(projection * view));
}

void enpitsu::Camera3D::tick(const float &delta)
{
    if(update)
    {
        updateMatrix(0.01f, 100);
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
    updateMatrix(0.1f, 100.0f);
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

bool enpitsu::Camera3D::isOrthogonal() const
{
    return orthogonal;
}

void enpitsu::Camera3D::setOrthogonal(bool orthogonal)
{
    Camera3D::orthogonal = orthogonal;
    update = true;
}

float enpitsu::Camera3D::getOffsetFromCenter() const
{
    return size.x / size.y;
}
