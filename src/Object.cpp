//
// Created by weekendUM on 1/24/2023.
//

#include "Object.h"
#include <iostream>

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
    listensInputEvents = dynamic_cast<InputEvents *>(this) != nullptr;
}

void enpitsu::Object::callKeyPressed(const enpitsu::KeyEvent &event)
{
    if(listensInputEvents)
    {
        dynamic_cast<InputEvents *>(this)->OnKeyPressed(event);
    }
}

void enpitsu::Object::callKeyReleased(const enpitsu::KeyEvent &event)
{
    if(listensInputEvents)
    {
        dynamic_cast<InputEvents *>(this)->OnKeyReleased(event);
    }
}
