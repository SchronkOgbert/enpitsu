//
// Created by weekendUM on 2/3/2023.
//

#ifndef LIBTEST_CONTROLOBJECT_H
#define LIBTEST_CONTROLOBJECT_H

#include "Object.h"

namespace enpitsu
{
    /**
     * An object that doesn't draw on the screen, but ticks nonetheless
     */
    class ControlObject : public Object
    {
    public:
        using Object::Object;

    protected:
        void draw() final;
    };

} // enpitsu

#endif //LIBTEST_CONTROLOBJECT_H
