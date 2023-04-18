//
// Created by weekendUM on 1/24/2023.
//

#include "enpitsu/objects/Object.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/helpers/InputEvents.h"

void enpitsu::Object::tick(const float &delta)
{
    this->draw();
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
//    println("destroying ", this);
}

bool enpitsu::Object::shouldUpdateCamera() const
{
    return screen->updateCamera;
}
