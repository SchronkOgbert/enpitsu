//
// Created by weekendUM on 1/26/2023.
//

#include "ObjectMaker.h"
#include "Screen.h"

ObjectMaker::ObjectMaker(void *screen) : AObject(screen)
{

}

void ObjectMaker::OnKeyPressed(const enpitsu::KeyEvent &event)
{
    if(event.event == enpitsu::KeyEvent::Event::KEY_A)
    {
        static_cast<enpitsu::Screen*>(this->screen)->addObject(
                std::make_shared<AObject>(this->screen)
                );
    }
}
