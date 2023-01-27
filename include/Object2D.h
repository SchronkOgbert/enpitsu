//
// Created by weekendUM on 1/27/2023.
//

#ifndef LIBTEST_OBJECT2D_H
#define LIBTEST_OBJECT2D_H

#include "Object.h"

namespace enpitsu
{
    class Object2D : public Object
    {
    public:
        using Object::Object;

    protected:
        void draw() override;
    };
}


#endif //LIBTEST_OBJECT2D_H
