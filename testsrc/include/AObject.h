//
// Created by weekendUM on 1/26/2023.
//

#ifndef ENPITSU_AOBJECT_H
#define ENPITSU_AOBJECT_H

#include "Object.h"
#include "InputEvents.h"

class AObject : public enpitsu::Object, public enpitsu::InputEvents
{
public:
    explicit AObject(void *screen);

    void OnKeyPressed(const enpitsu::KeyEvent &event) override;

    void OnMouseClick(const enpitsu::MouseEvent &event) override;

    void OnKeyReleased(const enpitsu::KeyEvent &event) override;
};


#endif //ENPITSU_AOBJECT_H
