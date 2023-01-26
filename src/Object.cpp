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
    std::cout << "Accept events: " << listensInputEvents << '\n';
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

void enpitsu::Object::draw()
{

}

enpitsu::Object::~Object()
{
    std::cout << "Object " << this << " destroyed\n";
}
