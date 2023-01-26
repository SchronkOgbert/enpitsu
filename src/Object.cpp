//
// Created by weekendUM on 1/24/2023.
//

#include "Object.h"
#include <iostream>

void Object::tick(const float &delta)
{
    this->draw();
}

void Object::callTick(const float &delta)
{
    this->tick(delta);
}

void Object::callInit()
{
    this->init();
}

void Object::init()
{

}
