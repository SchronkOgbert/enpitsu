//
// Created by weekendUM on 1/26/2023.
//

#include <iostream>
#include "AObject.h"

void AObject::OnKeyPressed(const enpitsu::KeyEvent &event)
{
    std::cout << "Key pressed: " << event.event << '\n';
}

void AObject::OnMouseClick(const enpitsu::MouseEvent &event)
{

}

void AObject::OnKeyReleased(const enpitsu::KeyEvent &event)
{

}
