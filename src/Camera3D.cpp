#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/InputEvents.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Object3D.h"
#include <format>

enpitsu::Camera3D::Camera3D(enpitsu::Screen *screen, const Vector3 &position, const Vector2 &size) :
        ControlObject(screen)
{
    this->size = size;
    this->position = position;
}

void enpitsu::Camera3D::OnMousePressed(const enpitsu::MouseEvent &event)
{
    PLOGD << "mouse pressed";
    if (event.button == MouseEvent::LEFT_MOUSE_BUTTON)
    {
        screen->showCursor(false);
        moving++;
    }
}

void enpitsu::Camera3D::OnMouseReleased(const enpitsu::MouseEvent &event)
{
    PLOGD << "mouse released";
    if (event.button == MouseEvent::LEFT_MOUSE_BUTTON)
    {
        screen->showCursor(true);
        moving--;
        PLOGD << std::format("Position: {}", position);
        PLOGD << std::format("Orientation: {}", orientation);
    }
}

void enpitsu::Camera3D::OnKeyPressed(const enpitsu::KeyEvent &event)
{
    PLOGD << "camera pressed key";
    switch (event.event)
    {
        case KeyEvent::KEY_A:
        {
            speedLeft++;
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
            speedLeft--;
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
    if(event.event == KeyEvent::KEY_A || event.event == KeyEvent::KEY_D)
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
    }
    else if (event.event == KeyEvent::KEY_S || event.event == KeyEvent::KEY_W)
    {
        switch (speedForward)
        {
            case -1:
            case 1:
                speedForward = 0;
                break;
            case 0:
                event.event == KeyEvent::KEY_S ? speedForward = -1 : speedForward = 1;
                break;
            default:
                speedForward = 0;
                break;
        }
        moving--;
    }
}

void enpitsu::Camera3D::updateMatrix(const float &FOV, const float &nearPlane, const float &farPlane,
                                     enpitsu::ShaderProgram *shaderProgram, const char *uniformName)
{
    *view = glm::lookAt(glm::vec3(position), glm::vec3(position) + glm::vec3(orientation), glm::vec3(up));
    auto lookat = (glm::vec3(position) + glm::vec3(orientation));
//    PLOGD << std::format("Position: {}", position);
//    PLOGD << std::format("Look at ({}, {}, {})", lookat.x, lookat.y, lookat.z);

    *projection = glm::perspective(glm::radians(FOV),
                                   static_cast<float>(size.x / size.y), nearPlane, farPlane);

    shaderProgram->updateMat4UniformF(uniformName, glm::value_ptr(*projection * *view));
}

void enpitsu::Camera3D::tick(const float &delta)
{
    /**
     * TODO make this more efficient
     * ideas:
     * 1. have the camera hold the references to all the 3D objects
     * 2. have the screen hold a reference of all the 3D objects(better since it's not guaranteed that there will
     * be a single camera, memory may be wasted if the camera holds them)
     * 3. have the object share shader objects(the best and most complex for many reasons) and only cycle
     * through the shaders directly to update them only once, not for every object
     */

    if (moving)
    {
        position += speed * speedLeft * glm::normalize(glm::cross(glm::vec3(orientation), glm::vec3(up)));
        position += speed * speedForward * glm::vec3(orientation);
//        PLOGD << std::format("camera moving to {}", position);
    }

    for (auto &object: *(screen->objects))
    {
        auto *tmp = dynamic_cast<Object3D *>(object.get());
        if (tmp)
        {
            updateMatrix(45, 0.1f, 100.0f,
                         tmp->getShaderProgram().get(), "camMatrix");
        } else
        {

        }
    }
    if (moving)
    {
    }
}
