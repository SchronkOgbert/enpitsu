#include "enpitsu/objects/Object.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/helpers/InputEvents.h"

void enpitsu::Object::tick(const float &delta)
{

}

void enpitsu::Object::callTick(const float &delta)
{
    this->tick(delta);
}

void enpitsu::Object::callInit()
{
    this->init();
}

void enpitsu::Object::init()
{
    
}

enpitsu::Object::~Object()
{
//    std::cout << "Object " << this << " destroyed\n";
}

enpitsu::Object::Object(Screen *screen)
{
    this->screen = screen;
}

void enpitsu::Object::destroy()
{
    this->onDestroy();
    queueDestroy = true;
    this->screen->removeObject(this);
}

void enpitsu::Object::onDestroy()
{

}

bool enpitsu::Object::shouldUpdateCamera3D() const
{
    return screen->updateCamera3D;
}

bool enpitsu::Object::shouldUpdateCamera2D() const
{
    return screen->updateCamera2D;
}

void enpitsu::Object::screenSizeChanged(const enpitsu::Vector2 &newSize)
{
    PLOGD << "Control Object: screen size changed";
}
