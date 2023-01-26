//
// Created by weekendUM on 1/26/2023.
//

#include "AScreen.h"

#include <memory>
#include "AObject.h"

void AScreen::init()
{
    Screen::init();
    for(int i = 0; i < 1000; i++)
    {
        addObject(std::make_shared<AObject>(this));
    }
}
