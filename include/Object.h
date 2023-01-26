//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_OBJECT_H
#define ENPITSU_OBJECT_H

#include "defines.h"

class Object
{
public:
    Object() = default;

    void callTick(const float& delta);

    void callInit();

protected:
    //events
    virtual void tick(const float &delta);

    virtual void init();

    virtual void draw() = 0;
};


#endif //ENPITSU_OBJECT_H
