//
// Created by weekendUM on 1/26/2023.
//

#ifndef ENPITSU_OBJECTMAKER_H
#define ENPITSU_OBJECTMAKER_H

#include "AObject.h"

class ObjectMaker : public AObject
{
public:
    explicit ObjectMaker(void *screen);

    void OnKeyPressed(const enpitsu::KeyEvent &event) override;
};


#endif //ENPITSU_OBJECTMAKER_H
