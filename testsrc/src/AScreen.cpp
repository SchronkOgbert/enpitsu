//
// Created by weekendUM on 1/26/2023.
//

#include "AScreen.h"

#include <memory>
#include "AObject.h"
#include "ObjectMaker.h"

void AScreen::init()
{
    Screen::init();
    addObject(std::make_shared<ObjectMaker>(this));
}
