#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Object3D.h"

enpitsu::Camera3D::Camera3D(enpitsu::Screen *screen, const Vector3 &position, const Vector2 &size) :
        ControlObject(screen)
{
    this->size = size;
    this->position = toGLMVec3(position);
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
    }
}

void enpitsu::Camera3D::OnKeyPressed(const enpitsu::KeyEvent &event)
{
    switch (event.event)
    {
        case KeyEvent::KEY_A:
        {
            position += speed * -glm::normalize(glm::cross(glm::vec3(orientation), glm::vec3(up)));
            break;
        }
        case KeyEvent::KEY_W:
        {
            position += speed * glm::vec3(orientation);
            break;
        }
        case KeyEvent::KEY_S:
        {
            position += speed * -glm::vec3(orientation);
            break;
        }
        case KeyEvent::KEY_D:
        {
            position += speed * glm::normalize(glm::cross(glm::vec3(orientation), glm::vec3(up)));
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
    if
            (
            event.event == KeyEvent::KEY_A ||
            event.event == KeyEvent::KEY_D ||
            event.event == KeyEvent::KEY_S ||
            event.event == KeyEvent::KEY_W
            )
    {
        moving--;
    }
}

void enpitsu::Camera3D::updateMatrix(const float &FOV, const float &nearPlane, const float &farPlane,
                                     const enpitsu::ShaderProgram *shaderProgram, const char *uniformName)
{
    glm::mat4 view(1.0f);
    view = glm::lookAt(glm::vec3 (position), glm::vec3 (position + orientation), glm::vec3 (up));

    glm::mat4 projection = glm::perspective(glm::radians(FOV),
                                            static_cast<float>(size.x / size.y), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), uniformName),
                       1, GL_FALSE, glm::value_ptr(projection * view));
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
    for (auto &object: *(screen->objects))
    {
        auto *tmp = dynamic_cast<Object3D *>(object.get());
        if (tmp)
        {
            updateMatrix(90, 0.1f, 100.0f,
                         tmp->getShaderProgram().get(), "camera");
        }
    }
    if (moving)
    {
    }
}
