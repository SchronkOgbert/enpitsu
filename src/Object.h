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

    //events
    virtual void tick();
};


#endif //ENPITSU_OBJECT_H
