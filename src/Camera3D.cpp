#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Object3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/transform.hpp"
#include <format>

enpitsu::Camera3D::Camera3D(enpitsu::Screen *screen, const Vector3 &position, const Vector2 &size) :
        ControlObject(screen)
{
    this->size = size;
    this->position = position;
}

void enpitsu::Camera3D::OnMousePressed(const enpitsu::MouseEvent &event)
{
    if (event.button == MouseEvent::LEFT_MOUSE_BUTTON)
    {
        justClicked = true;
        moving++;
    }
}

void enpitsu::Camera3D::OnMouseReleased(const enpitsu::MouseEvent &event)
{
    PLOGD << "mouse released";
    if (event.button == MouseEvent::LEFT_MOUSE_BUTTON)
    {
        moving--;
    }
}

void enpitsu::Camera3D::OnKeyPressed(const enpitsu::KeyEvent &event)
{
    if (!justClicked)
    {
        justClicked = true;
    }
    switch (event.event)
    {
        case KeyEvent::KEY_A:
        {
            speedLeft--;
            break;
        }
        case KeyEvent::KEY_W:
        {
            speedForward++;
            break;
        }
        case KeyEvent::KEY_S:
        {
            speedForward--;
            break;
        }
        case KeyEvent::KEY_D:
        {
            speedLeft++;
            break;
        }
        default:
        {
            return;
        }
    }
    moving++;
}

void enpitsu::Camera3D::OnKeyReleased(const enpitsu::KeyEvent &event)
{
    if (event.event == KeyEvent::KEY_A || event.event == KeyEvent::KEY_D)
    {
        switch (speedLeft)
        {
            case -1:
            case 1:
                speedLeft = 0;
                break;
            case 0:
                event.event == KeyEvent::KEY_D ? speedLeft = -1 : speedLeft = 1;
                break;
            default:
                speedLeft = 0;
                break;
        }
        moving--;
    } else if (event.event == KeyEvent::KEY_S || event.event == KeyEvent::KEY_W)
    {
        switch (speedForward)
        {
            case -1:
            case 1:
                speedForward = 0;
                break;
            case 0:
                event.event == KeyEvent::KEY_S ? speedForward = 1 : speedForward = -1;
                break;
            default:
                speedForward = 0;
                break;
        }
        moving--;
    }
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
    /**
     * TODO make this more efficient
     * ideas:
     * 1. have the camera hold the references to all the 3D objects
     * 2. have the screen hold a reference of all the 3D objects(better since it's not guaranteed that there will
     * be a single camera, memory may be wasted if the camera holds them)
     * 3. have the objects share shader objects(the best and most complex for many reasons) and only cycle
     * through the shaders directly to update them only once, not for every object
     * 4. in combination with 3 move the update in the objects' tick so that it doesn't needlessly bind and unbind shaders
     */

    move();
}

void enpitsu::Camera3D::move()
{
    /**
     * TODO move this from the library or make a separate camera class
     */
    if (this->moving)
    {
        // movement
        this->screen->showCursor(false);
        this->position +=
                this->speed * this->speedLeft * glm::normalize(glm::cross(glm::vec3(this->orientation), this->up));
        this->position += this->speed * this->speedForward * this->orientation;

        // orientation
        if (justClicked)
        {
            prevMousePos = this->screen->getMousePosition();
            justClicked = false;
        } else
        {
            prevMousePos = currMousePos;
        }
        currMousePos = this->screen->getMousePosition();
        float rotationX = mouseSensitivity * (currMousePos.x - prevMousePos.x);
        float rotationY = mouseSensitivity * (prevMousePos.y - currMousePos.y);

        yaw += rotationX;
        pitch += rotationY;

        if (pitch > 89) pitch = 89;
        if (pitch < -89) pitch = -89;

        Vector3 front(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                      sin(glm::radians(pitch)),
                      sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

        orientation = glm::normalize(front);
        updateMatrix(0.1f, 100.0f, "camMatrix");
    }
    else
    {
        this->screen->showCursor(true);
    }
}

const enpitsu::Vector3 &enpitsu::Camera3D::getPosition() const
{
    return position;
}

void enpitsu::Camera3D::setPosition(const enpitsu::Vector3 &position)
{
    this->position = position;
}

void enpitsu::Camera3D::init()
{
    Object::init();
    updateMatrix(0.1f, 100.0f, "camMatrix");
}
