//
// Created by weekendUM on 1/24/2023.
//

#include "Object.h"
#include "Screen.h"
#include <iostream>
#include "InputEvents.h"

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
    eventHandler = dynamic_cast<InputEvents *>(this);
    std::cout << "Accept events: " << (eventHandler != nullptr) << '\n';
}

void enpitsu::Object::callKeyPressed(const enpitsu::KeyEvent &event)
{
    if(eventHandler)
    {
        eventHandler->OnKeyPressed(event);
    }
}

void enpitsu::Object::callKeyReleased(const enpitsu::KeyEvent &event)
{
    if(eventHandler)
    {
        eventHandler->OnKeyReleased(event);
    }
}

enpitsu::Object::~Object()
{
    std::cout << "Object " << this << " destroyed\n";
}

enpitsu::Object::Object(Screen *screen)
{
    this->screen = screen;
}

void enpitsu::Object::destroy()
{
    this->onDestroy();
    this->screen->removeObject(this);
}

void enpitsu::Object::callMousePressed(const enpitsu::MouseEvent &event)
{
    if(eventHandler)
    {
        eventHandler->OnMousePressed(event);
    }
}

void enpitsu::Object::callMouseReleased(const enpitsu::MouseEvent &event)
{
    if(eventHandler)
    {
        eventHandler->OnMouseReleased(event);
    }
}

void enpitsu::Object::onDestroy()
{
    println("destroying ");
}
